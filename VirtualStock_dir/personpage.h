#ifndef PERSONPAGE_H
#define PERSONPAGE_H

#include <QWidget>
#include "global.h"
#include "chargepage.h"
#include "backdb.h"
#include <QString>
namespace Ui {
class Personpage;
}

class Personpage : public QWidget
{
    Q_OBJECT

public:
    explicit Personpage(QWidget *parent = nullptr);

    void openChargePage();

    ~Personpage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Personpage *ui;
};

#endif // PERSONPAGE_H
