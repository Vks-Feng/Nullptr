#ifndef NEWSWIDGET_H
#define NEWSWIDGET_H

#include <QWidget>
#include <QString>
#include <QListWidgetItem>
#include <QListWidget>
#include <QMessageBox>
#include <QDialog>
#include "newsdialog.h"
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
    std::map<int,std::vector<QString>> monthNews;
    void updateNews();
private slots:
    void onNewsItemClicked(QListWidgetItem *Item);

private:
    Ui::NewsWidget *ui;
    QListWidgetItem* currentItem;
    NewsDialog *newsDialog;
};

#endif // NEWSWIDGET_H
