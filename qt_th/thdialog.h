#ifndef TH_DIALOG_H
#define TH_DIALOG_H
#include <QtWidgets/QDialog>
#include <QtGui/QKeyEvent>
#include "thfish.h"

class THDialog:public QDialog{

public:
    THDialog(QWidget *parent=0);
    ~THDialog();

public:
    virtual void paintEvent(QPaintEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);

private:
    THFish *fish;
};

#endif
