/********************************************************************************
** Form generated from reading UI file 'polynomialmanage.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYNOMIALMANAGE_H
#define UI_POLYNOMIALMANAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PolynomialManage
{
public:
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_6;
    QSpinBox *spinBox;

    void setupUi(QWidget *PolynomialManage)
    {
        if (PolynomialManage->objectName().isEmpty())
            PolynomialManage->setObjectName(QString::fromUtf8("PolynomialManage"));
        PolynomialManage->resize(462, 133);
        pushButton_3 = new QPushButton(PolynomialManage);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(370, 50, 80, 24));
        pushButton_4 = new QPushButton(PolynomialManage);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(280, 80, 80, 24));
        lineEdit_2 = new QLineEdit(PolynomialManage);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 80, 261, 24));
        lineEdit_2->setMaxLength(255);
        lineEdit_2->setReadOnly(false);
        pushButton = new QPushButton(PolynomialManage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(370, 10, 80, 24));
        pushButton_2 = new QPushButton(PolynomialManage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(370, 80, 80, 24));
        lineEdit = new QLineEdit(PolynomialManage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 261, 24));
        lineEdit->setMaxLength(255);
        lineEdit->setReadOnly(true);
        label = new QLabel(PolynomialManage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 110, 441, 16));
        comboBox = new QComboBox(PolynomialManage);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(280, 50, 41, 24));
        pushButton_5 = new QPushButton(PolynomialManage);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(190, 50, 80, 24));
        lineEdit_3 = new QLineEdit(PolynomialManage);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(10, 50, 171, 24));
        lineEdit_3->setMaxLength(255);
        pushButton_6 = new QPushButton(PolynomialManage);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(280, 10, 80, 24));
        spinBox = new QSpinBox(PolynomialManage);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(330, 50, 31, 25));
        spinBox->setMinimum(1);
        spinBox->setMaximum(9);

        retranslateUi(PolynomialManage);

        QMetaObject::connectSlotsByName(PolynomialManage);
    } // setupUi

    void retranslateUi(QWidget *PolynomialManage)
    {
        PolynomialManage->setWindowTitle(QCoreApplication::translate("PolynomialManage", "Polynomial manage", nullptr));
        pushButton_3->setText(QCoreApplication::translate("PolynomialManage", "Derivative", nullptr));
        pushButton_4->setText(QCoreApplication::translate("PolynomialManage", "Add copy", nullptr));
        pushButton->setText(QCoreApplication::translate("PolynomialManage", "Delete", nullptr));
        pushButton_2->setText(QCoreApplication::translate("PolynomialManage", "Edit", nullptr));
        label->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("PolynomialManage", "a", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("PolynomialManage", "b", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("PolynomialManage", "c", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("PolynomialManage", "d", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("PolynomialManage", "e", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("PolynomialManage", "f", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("PolynomialManage", "g", nullptr));
        comboBox->setItemText(7, QCoreApplication::translate("PolynomialManage", "h", nullptr));
        comboBox->setItemText(8, QCoreApplication::translate("PolynomialManage", "i", nullptr));
        comboBox->setItemText(9, QCoreApplication::translate("PolynomialManage", "j", nullptr));
        comboBox->setItemText(10, QCoreApplication::translate("PolynomialManage", "k", nullptr));
        comboBox->setItemText(11, QCoreApplication::translate("PolynomialManage", "l", nullptr));
        comboBox->setItemText(12, QCoreApplication::translate("PolynomialManage", "m", nullptr));
        comboBox->setItemText(13, QCoreApplication::translate("PolynomialManage", "n", nullptr));
        comboBox->setItemText(14, QCoreApplication::translate("PolynomialManage", "o", nullptr));
        comboBox->setItemText(15, QCoreApplication::translate("PolynomialManage", "p", nullptr));
        comboBox->setItemText(16, QCoreApplication::translate("PolynomialManage", "q", nullptr));
        comboBox->setItemText(17, QCoreApplication::translate("PolynomialManage", "r", nullptr));
        comboBox->setItemText(18, QCoreApplication::translate("PolynomialManage", "s", nullptr));
        comboBox->setItemText(19, QCoreApplication::translate("PolynomialManage", "t", nullptr));
        comboBox->setItemText(20, QCoreApplication::translate("PolynomialManage", "u", nullptr));
        comboBox->setItemText(21, QCoreApplication::translate("PolynomialManage", "v", nullptr));
        comboBox->setItemText(22, QCoreApplication::translate("PolynomialManage", "w", nullptr));
        comboBox->setItemText(23, QCoreApplication::translate("PolynomialManage", "x", nullptr));
        comboBox->setItemText(24, QCoreApplication::translate("PolynomialManage", "y", nullptr));
        comboBox->setItemText(25, QCoreApplication::translate("PolynomialManage", "z", nullptr));

        pushButton_5->setText(QCoreApplication::translate("PolynomialManage", "Count", nullptr));
        pushButton_6->setText(QCoreApplication::translate("PolynomialManage", "Original", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PolynomialManage: public Ui_PolynomialManage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYNOMIALMANAGE_H
