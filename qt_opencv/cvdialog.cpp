#include "cvdialog.h"
#include <iostream>
CVDialog::CVDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::video()),
    video(new CVVideo()),
    type(0){
        ui->setupUi(this);
        QObject::connect(video, SIGNAL(sig_video(cv::Mat)), this, SLOT(show_video(cv::Mat)));
        video->start();
}

CVDialog::~CVDialog(){
    video->terminate();
    delete ui;
    delete video;
}

void CVDialog::gray(){
    type = 1;
}

void CVDialog::gauss(){
    type = 2;
}

void CVDialog::show_video(cv::Mat img){
    //添加图像处理
    if(type == 0){
        // 显示图像
        // 1.QImage
        QImage i_out(img.data, img.cols, img.rows, QImage::Format_BGR888);
        // 2.QPixmap
        QPixmap p_out = QPixmap::fromImage(i_out);
        // 3.显示到标签框
        ui->lbl_video->setPixmap(p_out);
        // 4.根据标签框大小显示图像
        ui->lbl_video->setScaledContents(true);
    }
    if(type == 1){
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        // 1.QImage
        QImage i_out(img.data, img.cols, img.rows, QImage::Format_Grayscale8);
        // 2.QPixmap
        QPixmap p_out = QPixmap::fromImage(i_out);
        // 3.显示到标签框
        ui->lbl_video->setPixmap(p_out);
        // 4.根据标签框大小显示图像
        ui->lbl_video->setScaledContents(true);
    }
    if(type == 2){
        // 高斯变换
        cv::GaussianBlur(img, img, cv::Size2i(17, 17), 3.0);
        // cv::Sobel(img, img, -1, 1, 1, 3,128); sobel变换
        // 1.QImage
        QImage i_out(img.data, img.cols, img.rows, QImage::Format_BGR888);
        // 2.QPixmap
        QPixmap p_out = QPixmap::fromImage(i_out);
        // 3.显示到标签框
        ui->lbl_video->setPixmap(p_out);
        // 4.根据标签框大小显示图像
        ui->lbl_video->setScaledContents(true);
    }
}