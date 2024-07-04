#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "buyin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();
    void on_personpage2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
