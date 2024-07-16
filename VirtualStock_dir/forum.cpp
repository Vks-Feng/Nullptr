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
    QHBoxLayout *mainLayout = new QHBoxLayout(this);


    // 创建左侧布局和按钮
    QWidget *left=new QWidget();
    mainLayout->addWidget(left);
    mainLayout->addWidget(scrollArea);
    QGridLayout *leftLayout = new QGridLayout();
    left->setLayout(leftLayout);
    QLabel *imageLabel = new QLabel();//放图
    imageLabel->setFixedSize(50,50);
    // 加载本地图片
    imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/conan.png); background-position:center;background-repeat:no-repeat;}");
    leftLayout->addWidget(imageLabel,0,0);

    // 创建提交刷新按钮
    QPushButton *submitButton = new QPushButton("我要发新帖");
    submitButton->setFixedWidth(100);
    submitButton->setStyleSheet("background-color:rgba(118, 163, 203, 100);");
    leftLayout->addWidget(submitButton, 0, 1);
    connect(submitButton, &QPushButton::clicked, this, &forum::onSubmitClicked);
    QPushButton *refreashButton = new QPushButton("刷新");
    refreashButton->setStyleSheet("background-color:rgba(118, 163, 203, 100)");
    refreashButton->setFixedWidth(50);
    leftLayout->addWidget(refreashButton, 0, 2);
    // 创建输入文本框
    com = new QTextEdit();
    com->setFixedHeight(400);
    com->setStyleSheet("background-color:rgba(118, 163, 203, 50)");

    leftLayout->addWidget(com, 1, 0,1,3);
    // 动态创建按钮并添加到布局中

    QRandomGenerator randomGenerator;
    int m=number.size();
    for (int row = 0; row < m; ++row) {
        QLabel *imageLabel = new QLabel();//放图
        // 加载本地图片
        imageLabel->setFixedSize(50,50);
        unsigned int r = randomGenerator.generate();
        if(r%4==0){
        // 加载本地图片
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black1.png); background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }
        else if(r%4==1){
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black2.png); background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }
        else if(r%4==2){
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black3.png); background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }
        else if(r%4==3){
            imageLabel->setStyleSheet("QLabel{ background-image: url(:/photos/black4.png); background-position:center;background-repeat:no-repeat;}");
            buttonLayout->addWidget(imageLabel,2*row,0);
        }


        // 创建按钮
        QPushButton *button ;
        QString temp="显示"+QString::number(m-row)+"号帖子详情";

        QString fix;
        int l=load[m-row-1].getcontent().size();
        for(int i=0;i<l;i+=30){
            fix+=load[m-row-1].getcontent().mid(i,28);
            fix+="\n";
        }
        button = new QPushButton(temp+"\n"+"发帖人："+load[m-row-1].getid()+"\n"+fix, this);
        button->setFixedHeight(100);
        button->setFixedWidth(350);
        button->setStyleSheet("QPushButton { font-size:16px}");
        button->setStyleSheet("QPushButton { text-align: left;background-color:rgba(118, 163, 203, 50) ; }");
        buttonLayout->addWidget(button, 2*row+1, 0);
        connect(button, &QPushButton::clicked, this, &forum::detail);
    }




    // //--vks--
    // connect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_Refresh, this, &forum::refresh);
    // //--vks--

    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

forum::~forum()
{
    // disconnect(Global::instance().getGlobalClient(), &ClientSocket::signal_Receive_Refresh, this, &forum::refresh);
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
    QString temp = com->toPlainText();

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


    //vks
    Global::instance().getGlobalClient()->write("RefreshPost:");
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

//void forum::refresh(){
//    forum*newforum=new forum();
//    newforum->show();
//    this->close();
//}
