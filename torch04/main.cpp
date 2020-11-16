#include <torch/torch.h>
#include <opencv2/opencv.hpp>

class lenet5 : public torch::nn::Module{

private:
    //卷积特征运算
    torch::nn::Conv2d conv1;
    torch::nn::Conv2d conv2;
    torch::nn::Conv2d conv3;

    torch::nn::Linear fc1;
    torch::nn::Linear fc2;

public:
    lenet5():
    conv1(torch::nn::Conv2dOptions(1, 6, 5).stride(1).padding(2)), // 1 * 28 * 28 -> 6 * 28 * 28 -> 6 * 24 * 24
    conv2(torch::nn::Conv2dOptions(6, 16, 5).stride(1).padding(0)), // 6 * 24 * 24 -> 16 * 10 * 10 -> 16 * 5 * 5
    conv3(torch::nn::Conv2dOptions(16, 120, 5).stride(1).padding(0)), // 16 * 5 * 5 -> 120 * 1 * 1(不需要池化)
    fc1(120, 84), // 120 -> 84
    fc2(84, 10){ // 84 -> 10
        // 注册需要学习的矩阵
        register_module("conv1", conv1);
        register_module("conv2", conv2);
        register_module("conv3", conv3);
        register_module("fc1", fc1);
        register_module("fc2", fc2);
    }

    //重载
    torch::Tensor forward(torch::Tensor x){
        // 1.conv1
        x = conv1->forward(x); // {n * 6 * 28 * 28}
        x = torch::max_pool2d(x, 2); // {n * 6 * 14 * 14}
        x = torch::relu(x); //激活函数

        // 2.conv2
        x = conv2->forward(x);
        x = torch::max_pool2d(x, 2);
        x = torch::relu(x);

        // 3.conv3
        x = conv3->forward(x);
        x = torch::relu(x);

        //做数据格式转换
        x = x.view({-1, 120});

        // 4.fc1
        x = fc1->forward(x);
        x = torch::relu(x);

        // 5.fc2
        x = fc2->forward(x);

        return torch::log_softmax(x, 1);

    }

}; 

template <typename DataLoader>
void train(std::shared_ptr<lenet5> &model, DataLoader &loader, torch::optim::Adam &optimizer){
    //迭代数据
    int n = 0;
    for(auto &batch : loader){
        auto data = batch.data;
        auto target = batch.target;
        optimizer.zero_grad(); //清空上一次的梯度

        //计算预测值
        torch::Tensor y = model->forward(data);

        //计算误差
        torch::Tensor loss = torch::nll_loss(y, target);

        //计算梯度：前馈求导
        loss.backward();

        //根据梯度更新参数矩阵
        optimizer.step();

        //std::cout << "\t--批次:" << std::setw(2) << std::setfill(' ') << ++n
        //          << ",\t损失值：" << std::setw(8) << std::setprecision(4) << loss.item<float>() << std::endl;
    }
}

template <typename DataLoader>
void valid(std::shared_ptr<lenet5> &model, DataLoader &loader){
    // 禁止求导的图跟踪
    torch::NoGradGuard no_grad;

    //循环测试集
    double sum_loss = 0.0;
    int32_t num_correct = 0;
    int32_t num_samples = 0;
    for(auto &batch : loader){
        //每个批次预测值
        auto data = batch.data;
        auto target = batch.target;
        num_samples += data.sizes()[0];
        auto y = model->forward(data);
        
        //计算纯预测的结果
        auto pred = y.argmax(1);

        //计算损失值
        sum_loss += torch::nll_loss(y, target, {}, at::Reduction::Sum).item<double>();

        //比较预测结果与真实的标签值
        num_correct += pred.eq(target).sum().item<int32_t>();
    }
    //输出正确值
    std::cout << std::setw(8) << std::setprecision(4)
        << "平均损失值：" << sum_loss / num_samples 
       << ",\t准确率：" << 100.0 * num_correct / num_samples  << "%" << std::endl;
}

int main(int argc, char **argv){
    // 数据集
    auto ds_train = torch::data::datasets::MNIST(".\\data",torch::data::datasets::MNIST::Mode::kTrain);
    auto ds_valid = torch::data::datasets::MNIST(".\\data",torch::data::datasets::MNIST::Mode::kTest);

    torch::data::transforms::Normalize<> norm(0.1307, 0.3081);
    torch::data::transforms::Stack<> stack;
    
    //数据批次加载器
    auto n_train = ds_train.map(norm);
    auto s_train = n_train.map(stack);
    auto train_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(s_train), 1000);

    auto n_valid = ds_train.map(norm);
    auto s_valid = n_valid.map(stack);
    auto valid_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(s_valid), 1000);

    // 1. 创建模型对象
    std::shared_ptr<lenet5> model = std::make_shared<lenet5>();
    //for(auto &batch : *train_loader){
    //    auto data = batch.data;
    //    auto target = batch.target;
    //    // 保证数据格式
    //    data = data.view({-1, 1, 28, 28});
    //    auto pred = model->forward(data);
    //    //pred与target存在误差，计算误差，计算调整5 * 5核矩阵的依据
    //}

    //优化器（管理模型中可训练矩阵）
    torch::optim::Adam optimizer = torch::optim::Adam(model->parameters(), torch::optim::AdamOptions(0.0001));

    std::cout << "开始训练" << std::endl;

    for(int e = 1; e <= 20; e ++){
        std::cout << "第" << e << "次训练!" << std::endl; 
        train(model, *train_loader, optimizer);
        if(e % 1 == 0){
            valid(model, *valid_loader);
        }
    }

    std::cout << "训练结束" << std::endl;
    torch::save(model, "lenet5.pt");

    return 0;
}
