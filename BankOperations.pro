#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T21:17:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainWindow
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    bankoperation.cpp \
    myclienttablemodel.cpp \
    taxedbankoperation.cpp \
    datagenerator.cpp

HEADERS  += mainwindow.h \
    bankoperation.h \
    tree.h \
    treenode.h \
    myclienttablemodel.h \
    bankbasetypes.h \
    taxedbankoperation.h \
    datagenerator.h

FORMS    += mainwindow.ui
