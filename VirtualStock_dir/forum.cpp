#include "forum.h"
#include "ui_forum.h"

forum::forum(QWidget *parent):QWidget(parent){
    time=Global:: instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    std::vector<Post>_load;//这里应当重新获取数据库中的表格
    _load=Global::instance().getGlobalDataBase()->getforum();
    allnumber=_load.size();
    for(int i=0;i<allnumber;i++){
        if(_load[i].getdate()>time){continue;}
        if(_load[i].getfatherid()==_load[i].getthisid()){
            load.push_back(_load[i]);
            number.push_back(_load[i].getfatherid());
            son.push_back(*new std::vector<Post>);
        }
        else{
            int m=number.size();
            for(int ii=0;ii<m;ii++){
                if(_load[i].getfatherid()==number[ii]){
                    son[ii].push_back(_load[i]);
                    break;
                }
            }
        }
    }
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
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    // 创建输入文本框
    QLineEdit *lineEdit = new QLineEdit();
    buttonLayout->addWidget(lineEdit, 0, 0); // 将文本框添加到第一行第一列

    // 创建提交按钮
    QPushButton *submitButton = new QPushButton("我要发新帖");
    buttonLayout->addWidget(submitButton, 0, 1); // 将提交按钮添加到第一行第二列

    // 连接提交按钮的clicked信号到槽函数
    connect(submitButton, &QPushButton::clicked, this, &forum::onSubmitClicked);

    QPushButton *refreashButton = new QPushButton("刷新");
    buttonLayout->addWidget(refreashButton, 0, 2); // 将提交按钮添加到第一行第二列
    connect(refreashButton, &QPushButton::clicked, this, &forum::refresh);

    // 动态创建按钮并添加到布局中


    int m=number.size();
    for (int row = 0; row < m; ++row) {
        // 创建按钮
        QPushButton *button ;
        QString temp="显示"+QString::number(m-row)+"号帖子详情";
        QString ttemp;

        int num=load[m-row-1].getdate();
        if(num!=13){
            ttemp="本帖发布时间为2023年"+QString::number(num)+"月";}
        else{
            ttemp="本帖发布时间为用户模拟结束后";}

        QString fix;
        int l=load[m-row-1].getcontent().size();
        for(int i=0;i<l;i+=40){
            fix+=load[m-row-1].getcontent().mid(i,40);
            fix+="\n";
        }
        button = new QPushButton(temp+"\n"+"发帖人："+load[m-row-1].getid()+"\n"+fix+"\n"+ttemp, this);
        button->setFixedHeight(300);
        button->setStyleSheet("QPushButton { font-size:32px}");



        buttonLayout->addWidget(button, row+1, 0,1,3);
        // 连接clicked信号到对应的槽函数
        connect(button, &QPushButton::clicked, this, &forum::detail);


    }


    ui->setupUi(this);
    showMaximized();
}

forum::~forum()
{
    delete ui;
}

void forum::detail(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString temp=button->text();
        qDebug()<<temp;
        int i=2;
        QString m;
        for(;i<5;i++){
            if(temp[i]>'9'||temp[i]<'0'){
                break;
            }
            m+=temp[i];
        }
        int n=m.toInt();
        // 可以在这里处理点击事件，比如打印按钮的文本
        display(n);
    }
}

void forum::onSubmitClicked() {

    // 读取文本框中的内容
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender()->parent()->findChild<QLineEdit*>());
    QString temp = lineEdit->text();
    if(temp==""){
        QMessageBox msgBox;
        msgBox.setText("发帖内容不能为空");
        msgBox.exec();
        return;
    }
    QString id = Global::instance().getGlobalUserManage()->GetUser(0)->GetName();

    //
    time=Global:: instance().getGlobalDataBase()->getTime(Global::instance().getGlobalUserManage()->GetUser(0)->GetId());
    std::vector<Post>_load;//这里应当重新获取数据库中的表格
    _load=Global::instance().getGlobalDataBase()->getforum();
    allnumber=_load.size();
    for(int i=0;i<allnumber;i++){
        if(_load[i].getdate()>time){continue;}
        if(_load[i].getfatherid()==_load[i].getthisid()){
            load.push_back(_load[i]);
            number.push_back(_load[i].getfatherid());
            son.push_back(*new std::vector<Post>);
        }
        else{
            int m=number.size();
            for(int ii=0;ii<m;ii++){
                if(_load[i].getfatherid()==number[ii]){
                    son[ii].push_back(_load[i]);
                    break;
                }
            }
        }
    }
    //

    Post add(time,temp,id,allnumber,allnumber);
    Global::instance().getGlobalDataBase()->addPost(add);
    //这里放上那个发帖链数据库的函数

    //vks
    Global::instance().getGlobalClient()->write("Refresh:");
    this->close();
    this->deleteLater();
    //vks

//    QMessageBox msgBox;
//    msgBox.setText("发帖成功");
//    msgBox.exec();
}

void forum::display(int m){
    std::vector<Post> temp;
    temp=son[m-1];
    temp.insert(temp.begin(),load[m-1]);
    sonforum *Sonforum=new sonforum(temp);
    Sonforum->show();
}

void forum::refresh(){
    forum*newforum=new forum();
    newforum->show();
    this->close();
}

