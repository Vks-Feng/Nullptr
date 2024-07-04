/********************************************************************************
** Form generated from reading UI file 'enroll.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENROLL_H
#define UI_ENROLL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_enroll
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
    QPushButton *LoginButton;

    void setupUi(QWidget *enroll)
    {
        if (enroll->objectName().isEmpty())
            enroll->setObjectName("enroll");
        enroll->resize(400, 300);
        LoginTitle = new QLabel(enroll);
        LoginTitle->setObjectName("LoginTitle");
        LoginTitle->setGeometry(QRect(100, 40, 221, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\344\273\277\345\256\213")});
        font.setPointSize(26);
        LoginTitle->setFont(font);
        line = new QFrame(enroll);
        line->setObjectName("line");
        line->setGeometry(QRect(60, 70, 281, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        verticalLayoutWidget = new QWidget(enroll);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(50, 110, 71, 80));
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

        verticalLayoutWidget_2 = new QWidget(enroll);
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

        LoginButton = new QPushButton(enroll);
        LoginButton->setObjectName("LoginButton");
        LoginButton->setGeometry(QRect(100, 230, 211, 24));
        LoginButton->setFlat(false);

        retranslateUi(enroll);

        QMetaObject::connectSlotsByName(enroll);
    } // setupUi

    void retranslateUi(QWidget *enroll)
    {
        enroll->setWindowTitle(QCoreApplication::translate("enroll", "Form", nullptr));
        LoginTitle->setText(QCoreApplication::translate("enroll", "\350\202\241\347\245\250\344\272\244\346\230\223\345\271\263\345\217\260", nullptr));
        UserNameLabel->setText(QCoreApplication::translate("enroll", "\347\224\250\346\210\267\345\220\215", nullptr));
        UserPasswordLabel->setText(QCoreApplication::translate("enroll", "\345\257\206 \347\240\201", nullptr));
        LoginButton->setText(QCoreApplication::translate("enroll", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class enroll: public Ui_enroll {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLL_H
