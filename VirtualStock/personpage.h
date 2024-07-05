#ifndef PERSONPAGE_H
#define PERSONPAGE_H

#include <QWidget>
<<<<<<< HEAD
#include "global.h"
=======
>>>>>>> a9b89b36e241c5019cc123393d20395c9374dba1

namespace Ui {
class Personpage;
}

class Personpage : public QWidget
{
    Q_OBJECT

public:
    explicit Personpage(QWidget *parent = nullptr);
    ~Personpage();

private:
    Ui::Personpage *ui;
};

#endif // PERSONPAGE_H
