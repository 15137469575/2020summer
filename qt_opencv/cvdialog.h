#ifndef CV_DIALOG_H
#define CV_DIALOG_H
#include <QtWidgets/QDialog>
#include "ui_video.h"
#include "cvvideo.h"

class CVDialog:public QDialog{
    Q_OBJECT
public:
    CVDialog(QWidget *parent=0);
    ~CVDialog();

private:
    Ui::video *ui;
    CVVideo *video;
    int type;
public slots:
    void gray();
    void gauss();
    void show_video(cv::Mat);
};

#endif
