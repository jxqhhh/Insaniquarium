#-------------------------------------------------
#
# Project created by QtCreator 2018-09-02T12:19:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Insaniquarium
TEMPLATE = app


SOURCES += main.cpp\
    gameinterface.cpp \
    gamewidget.cpp \
    ZObject/zfish.cpp \
    ZObject/zfood.cpp \
    ZObject/zobject.cpp \
    ZObject/zpet.cpp \
    ZObject/zscene.cpp \
    ZObject/zmoney.cpp \
    gamefaileddialog.cpp \
    Dialog.cpp \
    ZObject/zreminder.cpp \
    hintdialog_for_level2.cpp \
    ZObject/zalien.cpp \
    hintdialog_for_level3.cpp \
    hintdialog_for_level4.cpp \
    hintdialogforwin.cpp

HEADERS  += \
    gameinterface.h \
    gamewidget.h \
    ZObject/zfish.h \
    ZObject/zfood.h \
    ZObject/zobject.h \
    ZObject/zpet.h \
    ZObject/zscene.h \
    ZObject/zmoney.h \
    gamefaileddialog.h \
    Dialog.h \
    ZObject/zreminder.h \
    hintdialog_for_level2.h \
    ZObject/zalien.h \
    hintdialog_for_level3.h \
    hintdialog_for_level4.h \
    hintdialogforwin.h

FORMS    += \
    gameinterface.ui \
    gamewidget.ui \
    gamefaileddialog.ui \
    Dialog.ui \
    hintdialog_for_level2.ui \
    hintdialog_for_level3.ui \
    hintdialog_for_level4.ui \
    hintdialogforwin.ui

RESOURCES += \
    src.qrc
QMAKE_CXXFLAGS += -std=c++11
