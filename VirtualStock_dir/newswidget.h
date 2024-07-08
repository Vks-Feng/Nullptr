#ifndef NEWSWIDGET_H
#define NEWSWIDGET_H

#include <QWidget>
#include <QString>
#include "marketnews.h"
#include "global.h"

namespace Ui {
class NewsWidget;
}

class NewsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewsWidget(QWidget *parent = nullptr);
    ~NewsWidget();

    // std::vector<QString> news =
private:
    Ui::NewsWidget *ui;
};

#endif // NEWSWIDGET_H
