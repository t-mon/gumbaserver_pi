#-------------------------------------------------
#
# Project created by QtCreator 2013-03-10T19:35:12
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = gumbaserver_pi
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lqjson

SOURCES += main.cpp \
    core.cpp \
    tcpserver.cpp

HEADERS += \
    core.h \
    tcpserver.h
