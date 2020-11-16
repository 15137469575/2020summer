#include "thfish.h"

THFish::THFish(int x, int y, int m, int d):
    mouse(m),isopen(false),
    pos_x(x),pos_y(y),
    dir(d){

}

void THFish::run(){
    while(true){
        openMouse();
        //让窗体绘制最新的数据
        emit sign_open();
        QThread::usleep(100000);
    }
}

void THFish::openMouse(){
    if(isopen){
        mouse += 5;
        if(mouse >= 45){
             isopen = !isopen;
             mouse = 45;
        }
    }else{
        mouse -= 5;
        if(mouse <= 0){
             isopen = !isopen;
             mouse = 0;
        }
    }
}

void THFish::changeDir(int dir){
    this->dir = dir;
}

void THFish::swim(){
    if(this->dir == 0){
        pos_x += 2;
    }
    if(this->dir == 90){
        pos_y -= 2;
    }
    if(this->dir == 180){
        pos_x -= 2;
    }
    if(this->dir == 270){
        pos_y += 2;
    }
}

void THFish::showFish(QPainter *painter){
    QColor color(255, 0, 0, 255);
    QPen pen(color);
    painter->setPen(pen);
    painter->drawPie(pos_x, pos_y, 50, 50, mouse*16 + dir * 16, (360 - 2 * mouse)*16);
}
