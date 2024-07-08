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

void NewsWidget::updateNews(int month){
    std::map<int,std::vector<News>> newsMap =  Global::instance().getGlobalDataBase()->getNews(month);

    //用指定月的标题更新QListWidget
    for (auto& pair :newsMap) {
        std::vector<News>& newsVector = pair.second;
        updateNewsList(newsVector);
    }
}


void NewsWidget::updateNewsList(std::vector<News>& newsList)
{
    ui->NewsList->clear();

    for( auto& news : newsList){
        QString title = news.getTitle();
        QString content = news.getContent();
    }

}
