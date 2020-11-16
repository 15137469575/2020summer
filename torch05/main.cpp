#include <opencv2/opencv.hpp>
#include <torch/torch.h>

// 模型的实现（模型类）
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

//训练好的模型文件

//lenet5.pt

int main(){
    //加载模型
    std::shared_ptr<lenet5> model = std::make_shared<lenet5>();
    torch::load(model, "lenet5.pt");

    //使用测试集中数据识别
    auto imgs = torch::data::datasets::MNIST(".\\data", torch::data::datasets::MNIST::Mode::kTest);

    //取一张图像
    for(int i = 0; i < 10; i ++){
        torch::data::Example<> example = imgs.get(i);
        // std::cout << "识别的数字是：" << example.target.item<int32_t>() << std::endl;

        // 获取图像
        torch::Tensor a_img = example.data;

        //预测
        a_img = a_img.view({-1, 1, 28, 28});
        torch::Tensor y = model->forward(a_img);
        int32_t result = y.argmax(1).item<int32_t>();
        std::cout << "识别的结果是：" << result << "->" << example.target.item<int32_t>() << std::endl;
    }

    return 0;
}