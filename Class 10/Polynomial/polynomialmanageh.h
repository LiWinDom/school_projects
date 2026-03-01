#ifndef POLYNOMIALMANAGEH_H
#define POLYNOMIALMANAGEH_H

#include <QWidget>
#include "classes.h"
#include "functions.h"

namespace Ui {
class PolychelousManage;
}

class PolychelousManage : public QWidget
{
    Q_OBJECT

public:
    explicit PolychelousManage(QWidget *parent, Base* base, const uint16_t& index, QListWidget* listWidget);
    ~PolychelousManage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PolychelousManage *ui;

    Base* base;
    uint16_t index;
    QListWidget* listWidget;
};

#endif // POLYNOMIALMANAGEH_H
