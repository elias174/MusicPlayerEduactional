#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T18:14:17
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mp3Player
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp

HEADERS  += \
    mainwindow.h \
    adapterclass.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    imagesbuttons.qrc

unix:!macx: LIBS += -ltag
