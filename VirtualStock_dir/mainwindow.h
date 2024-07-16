#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QPlainTextEdit>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QApplication>
#include <QGraphicsBlurEffect>

#include "buyin.h"
#include "personpage.h"
#include "date.h"
#include "newswidget.h"
#include "forum.h"
#include "backdb.h"
#include "record.h"
#include "newswidget.h"
#include "dialog.h"
#include "forum.h"
#include "global.h"
#include "chartspline.h"
#include "report.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT


private:

public:
    explicit MainWindow(QWidget *parent = nullptr);
    int totalcurrency(int userID,int months);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    // void paintEvent(QPaintEvent *event) override;

private slots:

    void on_nextroundbutton_clicked();

    QString CompanyIntro(int index);

    void PutCompanyName_1(int index);

    void PutCompanyName_2(int index);

    void refreshForum();
    void showCustomDialog();


protected:

void closeEvent(QCloseEvent *event) override {
    disconnect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_Refresh, this, &MainWindow::refreshForum);

    QWidget::closeEvent(event);
}

private:
    Ui::MainWindow *ui;
    QPoint mousePoint;
    bool mouse_press;
    forum* forum_widget;
    buyin* buyin_widget;
};

#endif // MAINWINDOW_H
