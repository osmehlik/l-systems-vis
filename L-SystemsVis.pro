#-------------------------------------------------
#
# Project created by QtCreator 2013-11-10T21:54:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = L-SystemsVis
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lsystemview.cpp \
    lsystem.cpp \
    colorwidget.cpp \
    ruleseditorwidget.cpp \
    ruleeditorwidget.cpp

HEADERS  += mainwindow.h \
    lsystemview.h \
    lsystem.h \
    colorwidget.h \
    ruleseditorwidget.h \
    ruleeditorwidget.h

FORMS    += mainwindow.ui
