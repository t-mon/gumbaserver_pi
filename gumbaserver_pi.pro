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
include(qextserialport/src/qextserialport.pri)



SOURCES += main.cpp \
    core.cpp \
    tcpserver.cpp \
    serialconnection.cpp \
    servocontrol.cpp

HEADERS += \
    core.h \
    tcpserver.h \
    serialconnection.h \
    servocontrol.h
