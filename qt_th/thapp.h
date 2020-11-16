#ifndef TH_APP_H
#define TH_APP_H
#include <QtWidgets/QApplication>
#include "thdialog.h"

class THApp : public QApplication{

public:
    THApp(int argc, char **argv);
    ~THApp();

private:
    THDialog *dlg;
};

#endif
