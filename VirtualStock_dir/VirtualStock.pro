QT       += core gui
QT       += charts
QT       += sql

CONFIG += console
CONFIG -= app_bundle
LIBS += -lmysqlclient

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#win32:QMAKE_LFLAGS += -shared

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backdb.cpp \
    buyin.cpp \
    chargepage.cpp \
    chartspline.cpp \
    date.cpp \
    enroll.cpp \
    forum.cpp \
    global.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    marketnews.cpp \
    personpage.cpp \
    portfolio.cpp \
    post.cpp \
    record.cpp \
    sonforum.cpp \
    stock.cpp \
    user.cpp \
    usermanage.cpp \
    virtualcurrency.cpp \
    widget.cpp \
    newswidget.cpp

HEADERS += \
    LoginCreate.h \
    backdb.h \
    buyin.h \
    chargepage.h \
    chartspline.h \
    date.h \
    enroll.h \
    forum.h \
    global.h \
    login.h \
    mainwindow.h \
    mainwindow.h \
    marketnews.h \
    p2.h \
    personpage.h \
    portfolio.h \
    post.h \
    record.h \
    sonforum.h \
    stock.h \
    user.h \
    usermanage.h \
    virtualcurrency.h \
    widget.h \
    newswidget.h

FORMS += \
    buyin.ui \
    chargepage.ui \
    chartspline.ui \
    enroll.ui \
    forum.ui \
    login.ui \
    mainwindow.ui \
    personpage.ui \
    sonforum.ui \
    widget.ui \
    newswidget.ui

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


