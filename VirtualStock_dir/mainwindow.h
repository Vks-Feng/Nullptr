#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QMouseEvent>
#include "buyin.h"
#include "personpage.h"
#include "date.h"
#include "newswidget.h"
#include "forum.h"
#include "backdb.h"
#include "record.h"


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


private slots:

    // void on_personpage1_clicked();

    void on_nextroundbutton_clicked();

//    void on_TransactionButton_clicked();

    QString CompanyIntro(int index);

    void PutCompanyName_1(int index);

    void PutCompanyName_2(int index);

    void refreshForum();

private:
    Ui::MainWindow *ui;
    QPoint mousePoint;
    bool mouse_press;
    forum* forum_widget;
};

#endif // MAINWINDOW_H
