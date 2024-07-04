QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buyin.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    marketnews.cpp \
    portfolio.cpp \
    record.cpp \
    stock.cpp \
    user.cpp \
    usermanage.cpp \
    virtualcurrency.cpp \
    widget.cpp

HEADERS += \
    buyin.h \
    login.h \
    mainwindow.h \
    marketnews.h \
    p2.h \
    portfolio.h \
    record.h \
    stock.h \
    user.h \
    usermanage.h \
    virtualcurrency.h \
    widget.h

FORMS += \
    buyin.ui \
    login.ui \
    mainwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
