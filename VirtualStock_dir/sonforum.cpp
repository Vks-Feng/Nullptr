#include "sonforum.h"
#include "ui_sonforum.h"

sonforum::sonforum(std::vector<Post>_load,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sonforum)
{   time=Global:: instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    allnumber=_load.size();
    load=_load;
    // 创建一个QGridLayout来管理按钮布局
    buttonLayout = new QGridLayout(this);

    //创建滚动
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true); // 设置滚动区域可以调整大小

    // 创建一个QWidget作为滚动区域的子窗口
    QWidget *scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setLayout(buttonLayout); // 将网格布局设置到这个QWidget上

    // 将QWidget设置到滚动区域中
    scrollArea->setWidget(scrollAreaWidgetContents);

    // 创建一个布局并将滚动区域添加到主窗口中
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    // 创建左侧布局和按钮
    QWidget *left=new QWidget();

    QGridLayout *leftLayout = new QGridLayout();
    left->setLayout(leftLayout);
    QLabel *imageLabel = new QLabel();//放图
    imageLabel->setFixedSize(50,50);
    // 加载本地图片
    imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/conan.png); background-size: contain;background-position:center;background-repeat:no-repeat;}");
    leftLayout->addWidget(imageLabel,0,0);

    // 创建提交刷新按钮
    QPushButton *submitButton = new QPushButton("我要追帖");
    submitButton->setFixedWidth(100);
    leftLayout->addWidget(submitButton, 0, 1); // 将提交按钮添加到第一行第二列
    connect(submitButton, &QPushButton::clicked, this, &sonforum::onSubmitClicked);
    QPushButton *refreashButton = new QPushButton("刷新");
    refreashButton->setFixedWidth(50);
    leftLayout->addWidget(refreashButton, 0, 2);
    // 创建输入文本框
    com = new QTextEdit();
    com->setFixedHeight(400);
    leftLayout->addWidget(com, 1, 0,1,3); // 将文本框添加到第一行第一列
    // 动态创建按钮并添加到布局中
    mainLayout->addWidget(left);
    mainLayout->addWidget(scrollArea);


    // 动态创建按钮并添加到布局中
    QRandomGenerator randomGenerator;
    int m=load.size();
    for (int row = 0; row < m; ++row) {
        QLabel *imageLabel = new QLabel();
        imageLabel->setFixedSize(50,50);
        unsigned int r = randomGenerator.generate();
        if(r%4==0){
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black1.png); background-size: contain;background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }
        else if(r%4==1){
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black2.png); background-size: contain;background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }
        else if(r%4==2){
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black3.png); background-size: contain;background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }
        else if(r%4==3){
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black4.png); background-size: contain;background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }
        // 创建文本显示框
        QTextEdit *textEdit = new QTextEdit(this);
        textEdit->setReadOnly(true); // 设置为只读
        textEdit->setFixedHeight(300);
        buttonLayout->addWidget(textEdit, 2*row+1,0,1,3);
        // 可以在这里设置文本显示框的内容
        QString temp;
        int num=load[row].getdate();
        if(num!=13){
            temp="本帖发布时间为2023年"+QString::number(num)+"月";
            textEdit->setHtml("发帖人："+load[row].getid()+"<p>"+load[row].getcontent()+"<p>"+temp);}
        else{
            temp="本帖发布时间为用户模拟结束后";
            textEdit->setHtml("发帖人："+load[row].getid()+"<p>"+load[row].getcontent()+"<p>"+temp);
        }
        textEdit->setStyleSheet("QTextEdit { font-size:20px }");
    }
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

sonforum::~sonforum()
{
    delete ui;
}

void sonforum::onSubmitClicked() {
    // 读取文本框中的内容

    QString temp = com->toPlainText();
    QString id = Global::instance().getGlobalUserManage()->GetUser(0)->GetName();
    int fatherid=load[0].getthisid();

    time=Global:: instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    std::vector<Post>_load;//这里应当重新获取数据库中的表格
    _load=Global::instance().getGlobalDataBase()->getforum();
    allnumber=_load.size();
    int labal=load[0].getthisid();
    load.clear();
    for(int i =0;i<allnumber;i++){
        if(_load[i].getfatherid()==labal&&_load[i].getdate()<=time){
            load.push_back(_load[i]);
        }
    }
    //防止此人没刷新期间有人发帖导致编号错乱
    Post add(time,temp,id,fatherid,allnumber);
    Global::instance().getGlobalDataBase()->addPost(add);
    //这里放上那个发帖链数据库的函数
    QMessageBox msgBox;
    msgBox.setText("发帖成功");
    msgBox.exec();
    refreash();
}

void sonforum::refreash(){
    time=Global:: instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    std::vector<Post>_load;//这里应当重新获取数据库中的表格
    _load=Global::instance().getGlobalDataBase()->getforum();
    allnumber=_load.size();
    int labal=load[0].getthisid();
    load.clear();
    for(int i =0;i<allnumber;i++){
        if(_load[i].getfatherid()==labal&&_load[i].getdate()<=time){
            load.push_back(_load[i]);
        }
    }

    sonforum* newson=new sonforum(load);
    newson->show();
    this->close();
}
