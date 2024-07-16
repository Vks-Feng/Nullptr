#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QPlainTextEdit>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QApplication>
#include <QGraphicsBlurEffect>

#include "buyin.h"
#include "personpage.h"
#include "date.h"
#include "newswidget.h"
#include "forum.h"
#include "backdb.h"
#include "record.h"
#include "newswidget.h"
#include "dialog.h"
#include "forum.h"
#include "global.h"
#include "chartspline.h"
#include "qcustomplot.h"
#include "report.h"



namespace Ui {
class MainWindow;
}


class MyAxisTickerText : public QCPAxisTickerText
{
protected:
    virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE
    {
        Q_UNUSED(tickStep)
        QVector<double> result;
        if (mTicks.isEmpty())
            return result;

        auto start = mTicks.lowerBound(range.lower);
        auto end = mTicks.upperBound(range.upper);
        if (start != mTicks.constBegin()) --start;
        if (end != mTicks.constEnd()) ++end;

        int count = cleanMantissa(std::distance(start, end) / double(mTickCount + 1e-10));

        auto it = start;
        while (it != end) {
            result.append(it.key());
            int step = count;
            if (step == 0) ++it;
            while (--step >= 0 && it != end)
                ++it;
        }

        return result;
    }
};

class MainWindow : public QWidget
{
    Q_OBJECT


private:

public:
    explicit MainWindow(QWidget *parent = nullptr);
    int totalcurrency(int userID,int months);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setnew(int company_id);
    QVector<double> calculateMA(const QVector<QVector<double> > &v, int dayCount);

    // void paintEvent(QPaintEvent *event) override;

private slots:

    void on_nextroundbutton_clicked();

    QString CompanyIntro(int index);

    void PutCompanyName_1(int index);

    void PutCompanyName_2(int index);

    void refreshForum();
    void showCustomDialog();


    void on_ChooseWhichStock_1_currentIndexChanged(int index);

protected:

void closeEvent(QCloseEvent *event) override {
    disconnect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_Refresh, this, &MainWindow::refreshForum);

    QWidget::closeEvent(event);
}

private:
    Ui::MainWindow *ui;
    QPoint mousePoint;
    bool mouse_press;
    forum* forum_widget;
    buyin* buyin_widget;

    QCustomPlot* customPlot;

};

#endif // MAINWINDOW_H
