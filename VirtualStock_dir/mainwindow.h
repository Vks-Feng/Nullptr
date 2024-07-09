#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include "buyin.h"
#include "personpage.h"
#include "buyin.h"


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

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int extractMonthFromDate(const std::string& dateStr);
    std::vector<int> extractMonthsFromRecords(const std::vector<Record>& records);
private slots:

    void on_personpage1_clicked();

    void on_nextroundbutton_clicked();


    void on_communitybutton1_clicked();

    void on_TransactionButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
