#include "newswidget.h"
#include "ui_newswidget.h"

NewsWidget::NewsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NewsWidget),
    newsDialog(new NewsDialog(this))
{
    //内嵌子窗口
    ui->setupUi(this);
    // ui->NewsPicLabel->setScaledContents(true);
    ui->NewsPic2->setScaledContents(true);//自适应大小
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    currentItem = nullptr;
    connect(ui->NewsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onNewsItemClicked(QListWidgetItem*)));

    newsDialog = new NewsDialog(this);

    //设置图片阴影
    QGraphicsDropShadowEffect *newsshadow1 = new QGraphicsDropShadowEffect;
    // QGraphicsDropShadowEffect *newsshadow2 = new QGraphicsDropShadowEffect;
    newsshadow1->setBlurRadius(15); // 设置阴影的模糊半径
    newsshadow1->setColor(QColor(0, 0, 0, 150)); // 设置阴影颜色和透明度
    newsshadow1->setOffset(6, 6); // 设置阴影的偏移量
    // newsshadow2->setBlurRadius(10); // 设置阴影的模糊半径
    // newsshadow2->setColor(QColor(0, 0, 0, 150)); // 设置阴影颜色和透明度
    // newsshadow2->setOffset(4, 4); // 设置阴影的偏移量
    ui->NewsPic2->setGraphicsEffect(newsshadow1);
    // ui->NewsPicLabel->setGraphicsEffect(newsshadow2);
    // newsPic->setGraphicsEffect(newsshadow1);
    // // newsPic2.setGraphicsEffect(newsshadow1);


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


    QString newsARrray[13] =
    {
        " 2022年12月科技巨头股价表现分化：苹果、特斯拉逆势上涨，Meta、亚马逊等遭遇重挫",
        "2023年1月科技股市综述：苹果、特斯拉领涨，IBM、英特尔及Alphabet稳健上扬",
        "2023年2月科技股市亮点：苹果、特斯拉领涨，IBM与英特尔分红助力，亚马逊波动调整",
        "2023年3月科技股市概览：苹果、谷歌、特斯拉领涨，IBM与英特尔小幅上扬",
        "2023年4月科技股市回顾：苹果、谷歌稳步上扬，特斯拉波动中上涨，IBM转型受关注，英特尔分红支撑股价",
        "2023年5月科技股市亮点：苹果、谷歌、特斯拉领涨，IBM与英特尔小幅上扬",
        "2023年6月科技股市亮点：苹果、特斯拉领涨，IBM、英特尔与Alphabet各有表现",
        "2023年7月科技股市回顾：苹果、谷歌、特斯拉表现强劲，IBM与英特尔稳步上扬",
        "2023年8月科技股市概览：苹果、谷歌稳步前行，特斯拉股价波动中展现韧性，IBM与英特尔小幅调整",
        "2023年9月科技股市回顾：苹果稳中求进，IBM与谷歌面临波动，英特尔分红支撑，特斯拉股价微降但潜力依旧",
        "2023年10月科技股市回顾：苹果期待新品，IBM稳步转型，英特尔分红助力，谷歌微跌，特斯拉股价显著调整",
        "2023年11月科技股市亮点：苹果、IBM、英特尔、谷歌与特斯拉齐头并进",
        "2023年12月科技股市年终总结：苹果、IBM、英特尔、谷歌与特斯拉均展现强劲增长"
    };


    //用指定月的新闻更新QListWidget
    for (auto& pair :newsMap) {
        int month = pair.first;
         std::vector<QString> newsVector = pair.second;

        // 只添加月份信息，不添加具体新闻内容到列表中


         QString itemText = newsARrray[month];

        // QString("%1").arg(month)+newsARrray;

        QListWidgetItem *item = new QListWidgetItem(itemText);

        // 使用 QVariant 存储月份信息，方便后续获取
        QVariant monthVariant(month);
        item->setData(Qt::UserRole, monthVariant);
        ui->NewsList->addItem(item);
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





