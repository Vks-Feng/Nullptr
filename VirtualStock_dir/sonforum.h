#ifndef SONFORUM_H
#define SONFORUM_H

#include <QWidget>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "post.h"
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QApplication>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QObject>
#include <QMessageBox>
#include"global.h"
#include"post.h"
#include<QScrollArea>
#include <QScrollArea>
#include <QLabel>
#include <QRandomGenerator>
namespace Ui {
class sonforum;
}

class sonforum : public QWidget
{
    Q_OBJECT

public:
    explicit sonforum(std::vector<Post>_load,QWidget *parent = nullptr);
    ~sonforum();

private slots:
    void onSubmitClicked();
    void refreash();

private:
    int time;
    int allnumber;
    std::vector<Post>load;
    Ui::sonforum *ui;
    QGridLayout *buttonLayout;
    QTextEdit *com;
};

#endif // SONFORUM_H
