#include "thapp.h"

THApp::THApp(int argc, char **argv):
    QApplication(argc,argv),
    dlg(new THDialog){
    
    dlg->resize(600, 400);
    dlg->show();
}

THApp::~THApp(){
    delete dlg;
}
