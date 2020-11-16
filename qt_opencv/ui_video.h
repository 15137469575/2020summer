/********************************************************************************
** Form generated from reading UI file 'video.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEO_H
#define UI_VIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_video
{
public:
    QPushButton *btn_gray;
    QLabel *lbl_video;
    QPushButton *btn_gauss;

    void setupUi(QDialog *video)
    {
        if (video->objectName().isEmpty())
            video->setObjectName(QString::fromUtf8("video"));
        video->resize(794, 445);
        btn_gray = new QPushButton(video);
        btn_gray->setObjectName(QString::fromUtf8("btn_gray"));
        btn_gray->setGeometry(QRect(620, 110, 93, 28));
        lbl_video = new QLabel(video);
        lbl_video->setObjectName(QString::fromUtf8("lbl_video"));
        lbl_video->setGeometry(QRect(20, 20, 411, 411));
        btn_gauss = new QPushButton(video);
        btn_gauss->setObjectName(QString::fromUtf8("btn_gauss"));
        btn_gauss->setGeometry(QRect(620, 270, 93, 28));

        retranslateUi(video);
        QObject::connect(btn_gray, SIGNAL(clicked()), video, SLOT(gray()));
        QObject::connect(btn_gauss, SIGNAL(clicked()), video, SLOT(gauss()));

        QMetaObject::connectSlotsByName(video);
    } // setupUi

    void retranslateUi(QDialog *video)
    {
        video->setWindowTitle(QCoreApplication::translate("video", "\350\247\206\351\242\221\347\233\221\346\216\247", nullptr));
        btn_gray->setText(QCoreApplication::translate("video", "\347\201\260\345\272\246\345\217\230\346\215\242", nullptr));
        lbl_video->setText(QString());
        btn_gauss->setText(QCoreApplication::translate("video", "\351\253\230\346\226\257\345\217\230\346\215\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class video: public Ui_video {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEO_H
