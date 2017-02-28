#-------------------------------------------------
#
# Project created by QtCreator 2017-01-26T00:12:05
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simu
TEMPLATE = app

MOC_DIR = ./mocobj

OBJECTS_DIR = ./mocobj

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


win32{
INCLUDEPATH += D:/boost_1_62_0
}

SOURCES += \
    simumw.cpp \
    simumain.cpp

HEADERS  += \
    ../tmcsPi/ShareStruct.h \
    simumw.h

FORMS    += \
    simumw.ui
