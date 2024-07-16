#ifndef FORUM_H
#define FORUM_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "post.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QApplication>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QObject>
#include <QMessageBox>
#include"sonforum.h"
#include"global.h"
#include <QScrollArea>
#include <QLabel>
#include <QRandomGenerator>

namespace Ui {
class forum;
}

class forum : public QWidget
{
    Q_OBJECT

public:
    explicit forum(QWidget *parent=nullptr);
    ~forum();
    void display(int m);

private slots:
    void detail();
    void onSubmitClicked();
//    void refresh();

//vks
protected:

void closeEvent(QCloseEvent *event) override {
    QWidget::closeEvent(event);
}
//vks

private:
    int time;
    int allnumber;
    Ui::forum *ui;
    std::vector<Post>load;//父帖
    std::vector<int>number;//父帖id，便于查询
    std::vector<std::vector<Post>>son;//对应的子帖
    QGridLayout *buttonLayout;
    QTextEdit *com;
};

#endif // FORUM_H
