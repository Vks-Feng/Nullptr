#ifndef PERSONPAGE_H
#define PERSONPAGE_H
#include <QWidget>
namespace Ui{
class personpage;
}
class personpage: public QWidget
{
public:
    personpage();
private:
    Ui::personpage*ui;

};

#endif // PERSONPAGE_H
