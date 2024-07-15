QT       += core gui
QT       += charts
QT       += sql
QT       += network

CONFIG += console
CONFIG -= app_bundle

LIBS += -lmysqlclient

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

QMAKE_CXXFLAGS += -Wa,-mbig-obj
# 允许编译更大的文件

#unix {
#    QMAKE_CXXFLAGS -= -mbig-obj
#}
#取消编译选项特定于 Windows 上的 MinGW 工具链的

#win32:QMAKE_LFLAGS += -shared

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backdb.cpp \
    buyin.cpp \
    chargepage.cpp \
    chartspline.cpp \
    clientsocket.cpp \
    date.cpp \
    dialog.cpp \
    enroll.cpp \
    forum.cpp \
    global.cpp \
    istmcharts.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    news.cpp \
    newsdialog.cpp \
    personpage.cpp \
    portfolio.cpp \
    post.cpp \
    qcustomplot.cpp \
    record.cpp \
    risknotice.cpp \
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
    blurredFrame.h \
    buyin.h \
    chargepage.h \
    chartspline.h \
    clientsocket.h \
    date.h \
    dialog.h \
    enroll.h \
    forum.h \
    global.h \
    istmcharts.h \
    login.h \
    mainwindow.h \
    mainwindow.h \
    news.h \
    newsdialog.h \
    p2.h \
    personpage.h \
    portfolio.h \
    post.h \
    qcustomplot.h \
    record.h \
    risknotice.h \
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
    istmcharts.ui \
    login.ui \
    mainwindow.ui \
    newsdialog.ui \
    personpage.ui \
    risknotice.ui \
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

RESOURCES += \
    GroupLogo.qrc \
    Icon.qrc \
    back.qrc \
    backPerson1.qrc \
    communityIcon.qrc \
    forums.qrc \
    homeIcon.qrc \
    loginButton.qrc \
    loginPic.qrc \
    microsoft2.qrc \
    news4.qrc \
    newsPic.qrc \
    newsPic2.qrc \
    newsPic3.qrc \
    page1.qrc \
    peresonIcon.qrc \
    pullIcon.qrc \
    pullIcon3.qrc \
    pullIcon4.qrc \
    rankIcon.qrc \
    rechargeIcon.qrc \
    ruleIcon.qrc \
    trendIcon.qrc

DISTFILES += \
    photos/pullIcon3.png \
    photos/rank2.png \
    photos/rankIcon.png \
    photos/recharge.png \
    photos/stockIcon.png


