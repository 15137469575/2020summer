#include "cvvideo.h"
#include <iostream>

CVVideo::CVVideo(QObject *parent):
    QThread(parent),
    dev(new cv::VideoCapture(0, cv::CAP_DSHOW)){
    classifier = new cv::CascadeClassifier("haarcascade_frontalface_alt2.xml");

}

CVVideo::~CVVideo(){
    dev->release();
    delete classifier;
    delete dev;
}

void CVVideo::run(){
    while(true){
        //视频采集
        cv::Mat img;
        dev->read(img);

        // 图像如何处理
        //侦测人脸
        std::vector<cv::Rect> objs; // 用来存储识别的人脸
        std::vector<int> rejectLeves; // 返回拒绝的level
        std::vector<double> levelWeights; // level的权重

        classifier->detectMultiScale(
            img, //输入图像
            objs,
            rejectLeves,
            levelWeights,
            1.05, // 人脸搜索的模板
            3, //最小邻域个数限制
            1, //边缘检测（Canny）
            cv::Size(),
            cv::Size(),
            true
        );
        // 标记人脸
        if(!objs.empty()){
            for(int i = 0; i < objs.size(); i ++){
                if(levelWeights[i] >= 55.5){
                    cv::rectangle(img, objs[i], cv::Scalar(0, 0, 255), 2);
                }
            }
        }
        //视频图像发送到窗体显示
        emit sig_video(img);
        QThread::usleep(100000);
    }
}