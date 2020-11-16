//Qt GUI模块：Qtwidgets
//Qt 底层模块：Qtcore
//Qt 图形的绘制模块：QtGui
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

int main(int argc, char **argv){
    //1.构建Qt应用：QApplication
    QApplication app(argc, argv);
    //2.窗体构建：QDialog
    QDialog dlg;
    //窗体的属性(函数对getter/setter)
    dlg.setWindowTitle("Qt开发");
    dlg.resize(640,489);
    dlg.move(200,200);
    dlg.show();
    //3.信息循环处理
    int status = app.exec();
    //4.退出程序，返回状态码给系统int 4 字节()
    return status;
}

//dll所在的路径必须，必须设置到PATH路径中