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
#include <QTextEdit>>
#include <QApplication>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QObject>
#include <QMessageBox>
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
    void onnameButtonClicked() ;
    void onSubmitClicked();

private:
    Ui::sonforum *ui;
    QGridLayout *buttonLayout;
};

#endif // SONFORUM_H
