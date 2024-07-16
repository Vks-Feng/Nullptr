#ifndef NEWSDIALOG_H
#define NEWSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

namespace Ui {
class NewsDialog;
}

class NewsDialog : public QDialog {
    Q_OBJECT
public:
    NewsDialog(QWidget *parent = nullptr);
    ~NewsDialog();
    void setNewsText(const QString &text);

private:
    Ui::NewsDialog *ui;
    QLabel *newsLabel;
};


#endif // NEWSDIALOG_H
