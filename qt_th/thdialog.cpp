#include "thdialog.h"
#include <QtGui/QPainter>
THDialog::THDialog(QWidget *parent):
    QDialog(parent),
    fish(new THFish(100, 100)){
    QObject::connect(fish, SIGNAL(sign_open()), this, SLOT(repaint()));
    fish->start(); //线程启动
}

THDialog::~THDialog(){
    fish->terminate();
    delete fish;
}

void THDialog::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    fish->showFish(&painter);
}

void THDialog::keyPressEvent(QKeyEvent *e){
    if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Up){
        fish->changeDir(90);
        fish->swim();
    }
     if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Down){
        fish->changeDir(270);
        fish->swim();
    }
     if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Left){
        fish->changeDir(180);
        fish->swim();
    }
     if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Right){
        fish->changeDir(0);
        fish->swim();
    }
    this->repaint();
}
