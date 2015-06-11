#-------------------------------------------------
#
# Project created by QtCreator 2013-10-07T19:05:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DigitalProcess
TEMPLATE = app


SOURCES += main.cpp\
    templatesetting.cpp \
    setthreshold.cpp \
    linertransformsettingdialog.cpp \
    grayextenddialog.cpp \
    zoomdialog.cpp \
    submainwindow.cpp \
    parameterdialog.cpp \
    mainwindow.cpp \
    imageprocessing.cpp \
    drawhistogram.cpp

HEADERS  += \
    templatesetting.h \
    setthreshold.h \
    linertransformsettingdialog.h \
    grayextenddialog.h \
    zoomdialog.h \
    submainwindow.h \
    parameterdialog.h \
    mainwindow.h \
    imageprocessing.h \
    drawhistogram.h

FORMS    += mainwindow.ui \
    templatesetting.ui \
    setthreshold.ui \
    linertransformsettingdialog.ui \
    grayextenddialog.ui \
    zoomdialog.ui \
    parameterdialog.ui

RESOURCES += \
    res.qrc

RC_FILE = res/myapp.rc
