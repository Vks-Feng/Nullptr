#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "buyin.h"
#include "personpage.h"


#include "date.h"
#include "newswidget.h"


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

    void on_buyinButton_clicked();

    void on_personpage1_clicked();

    void on_nextroundbutton_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
