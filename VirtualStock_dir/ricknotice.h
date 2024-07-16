#ifndef RICKNOTICE_H
#define RICKNOTICE_H

#include <QDialog>

namespace Ui {
class RickNotice;
}

class RickNotice : public QDialog
{
    Q_OBJECT

public:
    explicit RickNotice(QWidget *parent = nullptr);
    ~RickNotice();

private:
    Ui::RickNotice *ui;
};

#endif // RICKNOTICE_H
