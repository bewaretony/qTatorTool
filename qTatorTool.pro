QT              += core gui network

CONFIG          += c++11
QMAKE_CXXFLAGS  += -Werror

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qTatorTool
TEMPLATE = app

INCLUDEPATH += src

SOURCES += src/main.cpp\
        src/tatortool.cpp \
    src/logitem.cpp \
    src/logtablemodel.cpp \
    src/logtable.cpp \
    src/console.cpp \
    src/netconsolereceiver.cpp

HEADERS  += src/tatortool.h \
    src/logitem.h \
    src/logtype.h \
    src/logtablemodel.h \
    src/logtable.h \
    src/console.h \
    src/netconsolereceiver.h

FORMS    += ui/tatortool.ui \
    ui/logtable.ui \
    ui/console.ui

DISTFILES += \
    console_test.py

RESOURCES += \
    resource/icon.qrc
