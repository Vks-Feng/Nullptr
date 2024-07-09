#include "newswidget.h"
#include "ui_newswidget.h"

NewsWidget::NewsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NewsWidget)
{
    //内嵌子窗口
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    currentItem = nullptr;
}

NewsWidget::~NewsWidget()
{
    delete ui;
}

void NewsWidget::updateNews(){


    std::map<int,std::vector<QString>> newsMap =  Global::instance().getGlobalDataBase()->getNews(month);


    ui->NewsList->clear();

    //用指定月的新闻更新QListWidget
    for (auto& pair :newsMap) {

        std::vector<QString>& newsVector = pair.second;

        for(QString& newsContent : newsVector)
        {
            QListWidgetItem *item = new QListWidgetItem(newsContent);
            ui->NewsList->addItem(item);
        }
    }
}



