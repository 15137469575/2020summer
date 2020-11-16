# 控制编译器c++相关的编译选项
QMAKE_CXXFLAGS += /source-charset:utf-8
QMAKE_CXXFLAGS += /execution-charset:utf-8

# 配置程序的类型：应用/共享库
TEMPLATE = app

# 基本配置
CONFIG += debug
CONFIG += console
CONFIG += thread
CONFIG += qt

#opencv的链接的相关的库与头文件
INCLUDEPATH +="E:\OPENCV\install\include"

LIBS += -L"E:\OPENCV\install\x64\vc16\lib"
LIBS += -lopencv_core420d
LIBS += -lopencv_videoio420d
LIBS += -lopencv_imgcodecs420d
LIBS += -lopencv_imgproc420d
LIBS += -lopencv_objdetect420d

# Qt的模块库的配置
QT += core
QT += gui
QT += widgets

# 工程代码文件
SOURCES += main.cpp
SOURCES += cvvideo.cpp
SOURCES += cvdialog.cpp

HEADERS += cvdialog.h
HEADERS += cvvideo.h

FORMS += video.ui

# 输出的执行文件
TARGET += main

