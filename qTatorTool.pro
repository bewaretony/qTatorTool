#-------------------------------------------------
#
# Project created by QtCreator 2015-11-15T12:21:05
#
#-------------------------------------------------

QT              += core gui network

CONFIG          += c++11
QMAKE_CXXFLAGS  += -Werror

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qTatorTool
TEMPLATE = app


SOURCES += main.cpp\
        tatortool.cpp \
    logitem.cpp \
    logtablemodel.cpp \
    logtable.cpp

HEADERS  += tatortool.h \
    logitem.h \
    logtype.h \
    logtablemodel.h \
    logtable.h

FORMS    += tatortool.ui \
    logtable.ui
