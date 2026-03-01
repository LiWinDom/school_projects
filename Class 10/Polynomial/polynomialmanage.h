#ifndef POLYNOMIALMANAGE_H
#define POLYNOMIALMANAGE_H

#include <QWidget>
#include "classes.h"
#include "functions.h"

namespace Ui {
class PolynomialManage;
}

class PolynomialManage : public QWidget
{
    Q_OBJECT

public:
    explicit PolynomialManage(QWidget *parent, Base* base, const uint16_t& index, QListWidget* listWidget, QListWidget* listWidget_2);
    ~PolynomialManage();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_lineEdit_2_returnPressed();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_3_returnPressed();

private:
    Ui::PolynomialManage *ui;

    Base* base;
    uint16_t index;
    QListWidget* listWidget, *listWidget_2;
};

#endif // POLYNOMIALMANAGE_H
