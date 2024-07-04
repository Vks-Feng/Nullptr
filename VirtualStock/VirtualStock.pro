QT       += core gui
QT       += charts
QT       += sql

CONFIG += console
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#win32:QMAKE_LFLAGS += -shared

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backdb.cpp \
    backendwithdatabase2.cpp \
    buyin.cpp \
    chartspline.cpp \
    enroll.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    marketnews.cpp \
    personpage.cpp \
    portfolio.cpp \
    querywidget.cpp \
    record.cpp \
    stock.cpp \
    user.cpp \
    usermanage.cpp \
    virtualcurrency.cpp \
    widget.cpp

HEADERS += \
    LoginCreate.h \
    backdb.h \
    backendwithdatabase2.h \
    buyin.h \
    chartspline.h \
    enroll.h \
    login.h \
    mainwindow.h \
    marketnews.h \
    p2.h \
    personpage.h \
    portfolio.h \
    querywidget.h \
    record.h \
    stock.h \
    user.h \
    usermanage.h \
    virtualcurrency.h \
    widget.h

FORMS += \
    buyin.ui \
    chartspline.ui \
    enroll.ui \
    login.ui \
    mainwindow.ui \
    personpage.ui \
    querywidget.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


### 1. Add the llibmysql
win32: LIBS += -L$$PWD/../lib/ -llibmysql

INCLUDEPATH += $$PWD/../_include
DEPENDPATH += $$PWD/../_include


### 2. Add the libmysqlclient
win32: LIBS += -L$$PWD/../lib/ -lmysqlclient

INCLUDEPATH += $$PWD/../_include
DEPENDPATH += $$PWD/../_include


