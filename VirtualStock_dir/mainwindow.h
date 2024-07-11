#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QMouseEvent>
#include "buyin.h"
#include "personpage.h"
#include "buyin.h"


#include "date.h"
#include "newswidget.h"
#include "forum.h"
#include "backdb.h"
#include "record.h"
#include "newswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    int totalcurrency();
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private slots:

    void on_personpage1_clicked();

    void on_nextroundbutton_clicked();


    void on_communitybutton1_clicked();

    void on_TransactionButton_clicked();


private:
    Ui::MainWindow *ui;
    QPoint mousePoint;
    bool mouse_press;
};

#endif // MAINWINDOW_H
