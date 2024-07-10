#include "newswidget.h"
#include "ui_newswidget.h"

NewsWidget::NewsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NewsWidget),
    newsDialog(new NewsDialog(this))
{
    //内嵌子窗口
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    currentItem = nullptr;
    connect(ui->NewsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onNewsItemClicked(QListWidgetItem*)));

    newsDialog = new NewsDialog(this);
}

NewsWidget::~NewsWidget()
{
    delete newsDialog;
    delete ui;
}

void NewsWidget::updateNews(){
    int user_ID = Global::instance().getGlobalUserManage()->GetUser(0)->GetId();
    int month = Global::instance().getGlobalDataBase()->getTime(user_ID);
    std::map<int,std::vector<QString>> newsMap =  Global::instance().getGlobalDataBase()->getNews(month);


    ui->NewsList->clear();

    //用指定月的新闻更新QListWidget
    for (auto& pair :newsMap) {
        int month = pair.first;
         std::vector<QString> newsVector = pair.second;

        // 只添加月份信息，不添加具体新闻内容到列表中
        QString itemText = QString("%1").arg(month);
        QListWidgetItem *item = new QListWidgetItem(itemText);

        // 使用 QVariant 存储月份信息，方便后续获取
        QVariant monthVariant(month);
        item->setData(Qt::UserRole, monthVariant);
        ui->NewsList->addItem(item);
        qDebug()<<month;
    }

}


void NewsWidget::onNewsItemClicked(QListWidgetItem *item){
    QVariant monthVariant = item ->data(Qt::UserRole);
    int month = monthVariant.toInt();

    // 根据月份获取新闻内容并显示弹窗
    std::vector<QString> newsVector = Global::instance().getGlobalDataBase()->getNews(month)[month];

    QString newsText;
    for (const QString& news : newsVector) {
        newsText += news + "\n";
    }

    newsDialog->setNewsText(newsText); // Set news content
    newsDialog->adjustSize();
    newsDialog->exec(); // Show dialog
}



