#ifndef PERSONPAGE_H
#define PERSONPAGE_H

#include <QWidget>

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
