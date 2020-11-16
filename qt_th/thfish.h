#ifndef TH_FISH_H
#define TH_FISH_H
#include <QtCore/QThread>
#include <QtGui/QPainter>

class THFish : public QThread{
    Q_OBJECT
public:
    THFish(int x= 0, int y = 0, int m = 45, int d = 0);
    void openMouse();
    void changeDir(int dir);
    void swim();
    void showFish(QPainter *painter);

protected:
    virtual void run();

private:
    int mouse;
    int pos_x, pos_y;
    int dir;
    bool isopen;

signals:
    void sign_open();
};

#endif
