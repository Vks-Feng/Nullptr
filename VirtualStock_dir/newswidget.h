#ifndef NEWSWIDGET_H
#define NEWSWIDGET_H

#include <QWidget>
#include <QString>
#include <QListWidgetItem>
#include "news.h"
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

    void updateNews(int month);
    void updateNewsList(const std::vector<News>& newList);
private:
    Ui::NewsWidget *ui;
    QListWidgetItem* currentItem;
};

#endif // NEWSWIDGET_H
