#ifndef PERSONPAGE_H
#define PERSONPAGE_H

#include <QWidget>
#include "global.h"
#include "chargepage.h"

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

private:
    Ui::Personpage *ui;
};

#endif // PERSONPAGE_H
