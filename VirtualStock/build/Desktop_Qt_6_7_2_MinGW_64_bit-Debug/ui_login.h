/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *LoginTitle;
    QFrame *line;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *UserNameLabel;
    QLabel *UserPasswordLabel;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *UserNameInput;
    QLineEdit *UserPasswordInput;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *RegisterButton;
    QPushButton *DetailButton;
    QPushButton *LoginButton;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(400, 292);
        LoginTitle = new QLabel(Login);
        LoginTitle->setObjectName("LoginTitle");
        LoginTitle->setGeometry(QRect(90, 30, 221, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font.setPointSize(26);
        LoginTitle->setFont(font);
        line = new QFrame(Login);
        line->setObjectName("line");
        line->setGeometry(QRect(60, 70, 281, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        verticalLayoutWidget = new QWidget(Login);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(60, 100, 71, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        UserNameLabel = new QLabel(verticalLayoutWidget);
        UserNameLabel->setObjectName("UserNameLabel");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font1.setPointSize(14);
        UserNameLabel->setFont(font1);

        verticalLayout->addWidget(UserNameLabel);

        UserPasswordLabel = new QLabel(verticalLayoutWidget);
        UserPasswordLabel->setObjectName("UserPasswordLabel");
        UserPasswordLabel->setFont(font1);

        verticalLayout->addWidget(UserPasswordLabel);

        verticalLayoutWidget_2 = new QWidget(Login);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(150, 100, 191, 91));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        UserNameInput = new QLineEdit(verticalLayoutWidget_2);
        UserNameInput->setObjectName("UserNameInput");

        verticalLayout_2->addWidget(UserNameInput);

        UserPasswordInput = new QLineEdit(verticalLayoutWidget_2);
        UserPasswordInput->setObjectName("UserPasswordInput");

        verticalLayout_2->addWidget(UserPasswordInput);

        horizontalLayoutWidget = new QWidget(Login);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 240, 401, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        RegisterButton = new QPushButton(horizontalLayoutWidget);
        RegisterButton->setObjectName("RegisterButton");
        RegisterButton->setFlat(true);

        horizontalLayout->addWidget(RegisterButton);

        DetailButton = new QPushButton(horizontalLayoutWidget);
        DetailButton->setObjectName("DetailButton");
        DetailButton->setFlat(true);

        horizontalLayout->addWidget(DetailButton);

        LoginButton = new QPushButton(Login);
        LoginButton->setObjectName("LoginButton");
        LoginButton->setGeometry(QRect(90, 200, 211, 24));
        LoginButton->setFlat(false);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        LoginTitle->setText(QCoreApplication::translate("Login", "\350\202\241\347\245\250\344\272\244\346\230\223\345\271\263\345\217\260", nullptr));
        UserNameLabel->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        UserPasswordLabel->setText(QCoreApplication::translate("Login", "\345\257\206 \347\240\201", nullptr));
        RegisterButton->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        DetailButton->setText(QCoreApplication::translate("Login", "\350\257\246\346\203\205", nullptr));
        LoginButton->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
