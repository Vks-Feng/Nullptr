#include "newsdialog.h"
#include "ui_newsdialog.h"

NewsDialog::NewsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewsDialog)
{
    ui->setupUi(this);
    setWindowTitle("News Details");
    setFixedSize(500,500);

    QVBoxLayout *layout = new QVBoxLayout(this);
    newsLabel = new QLabel(this);
    newsLabel->setWordWrap(true); // 自动换行
    layout->addWidget(newsLabel);


    QPushButton *closeButton = new QPushButton("Close", this);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
    setLayout(layout);
}


NewsDialog::~NewsDialog()
{
    delete ui;
}

void NewsDialog::setNewsText(const QString &text) {
    newsLabel->setText(text);
}
