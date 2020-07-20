#ifndef COMMON_H
#define COMMON_H

#include <QString>

const QString g_strRedBtnStyleSheet = "QPushButton {color: rgb(255, 255, 255); border-radius:150px; background-color:rgb(255, 0, 0);} \
        QPushButton:hover {color:rgb(255, 255, 255); border-radius:150px; background-color:rgb(255, 85, 127);} \
        QPushButton:pressed {color:rgb(255, 85, 127); border-width:3; border-color:rgb(255, 0, 0); border-style:solid; background-color:cyan;}";

const QString g_strBlueBtnStyleSheet = "QPushButton { color: rgb(255, 255, 255); border-radius:150px; background-color:rgb(85, 170, 255); } \
        QPushButton:hover {color:rgb(255, 255, 255); border-radius:150px; background-color:rgb(170, 255, 255);} \
        QPushButton:pressed {color:rgb(255, 85, 127); border-width:3; border-color:rgb(255, 0, 0); border-style:solid; background-color:rgb(170, 255, 255);}";

#endif // COMMON_H
