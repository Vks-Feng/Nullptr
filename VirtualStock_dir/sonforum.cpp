#include "sonforum.h"
#include "ui_sonforum.h"

sonforum::sonforum(std::vector<Post>load,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sonforum)
{
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

    // 动态创建按钮并添加到布局中
    int m=load.size();
    for (int row = 0; row < m; ++row) {
        // 创建按钮
        QPushButton *button = new QPushButton(load[row].getid(), this);
        buttonLayout->addWidget(button, row+1, 0);
        // 连接clicked信号到对应的槽函数
        connect(button, &QPushButton::clicked, this, &sonforum::onnameButtonClicked);

        // 创建文本显示框
        QTextEdit *textEdit = new QTextEdit(this);
        textEdit->setReadOnly(true); // 设置为只读
        buttonLayout->addWidget(textEdit, row+1, 2);

        // 可以在这里设置文本显示框的内容
        textEdit->setHtml(load[row].getcontent());
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


    QMessageBox msgBox;
    msgBox.setText("发帖成功");
    msgBox.exec();
}
