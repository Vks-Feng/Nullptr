#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QueryWidget : public QMainWindow
{
    Q_OBJECT

public:
    QueryWidget(QWidget *parent = nullptr);

    ~QueryWidget();

public slots:
    PerformQuery();

private:
    Ui::MainWindow *ui;
};
#endif // QUERYWIDGET_H
