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

    // 创建输入文本框
    QLineEdit *lineEdit = new QLineEdit();
    buttonLayout->addWidget(lineEdit, 0, 0); // 将文本框添加到第一行第一列

    // 创建提交按钮
    QPushButton *submitButton = new QPushButton("我要追帖");
    buttonLayout->addWidget(submitButton, 0, 1); // 将提交按钮添加到第一行第二列

    // 连接提交按钮的clicked信号到槽函数
    connect(submitButton, &QPushButton::clicked, this, &sonforum::onSubmitClicked);

    QPushButton *refreashButton = new QPushButton("刷新");
    buttonLayout->addWidget(refreashButton, 0, 2); // 将提交按钮添加到第一行第三列
    connect(refreashButton, &QPushButton::clicked, this, &sonforum::refreash);


    // 动态创建按钮并添加到布局中
    int m=load.size();
    for (int row = 0; row < m; ++row) {
        // 创建文本显示框
        QTextEdit *textEdit = new QTextEdit(this);
        textEdit->setReadOnly(true); // 设置为只读
        buttonLayout->addWidget(textEdit, row+1,0);
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
    }
    ui->setupUi(this);
}

sonforum::~sonforum()
{
    delete ui;
}
void sonforum::onnameButtonClicked() {
    // sender()方法返回信号发送者对象的指针，这里就是被点击的按钮
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        // 在这里处理点击事件
    }

}

void sonforum::onSubmitClicked() {
    // 读取文本框中的内容
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender()->parent()->findChild<QLineEdit*>());
    QString temp = lineEdit->text();
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
