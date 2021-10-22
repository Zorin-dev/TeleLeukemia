#-------------------------------------------------
#
# Project created by QtCreator 2017-03-28T22:10:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network printsupport

TARGET = TeleLeukemia
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cellparams.cpp \
    dialog.cpp \
    mygraphicsobject.cpp \
    propdialog.cpp \
    showwidget.cpp \
    widget.cpp \
    netdialog.cpp \
    myserver.cpp \
    myclient.cpp \
    classifier.cpp \
    cellslocation.cpp \
    databaseprocessor.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    cellparams.h \
    dialog.h \
    mygraphicsobject.h \
    propdialog.h \
    showwidget.h \
    widget.h \
    netdialog.h \
    myserver.h \
    myclient.h \
    classifier.h \
    cellslocation.h \
    databaseprocessor.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    dialog.ui \
    showwidget.ui \
    widget.ui \
    netdialog.ui \
    propdialog.ui \
    classifier.ui \
    cellslocation.ui




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -lqtcsv1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lqtcsv1d

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
