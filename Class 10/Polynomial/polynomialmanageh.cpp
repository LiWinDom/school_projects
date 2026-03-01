#include "polynomialmanageh.h"
#include "ui_polynomialmanage.h"

PolynomialManage::PolynomialManage(QWidget *parent, Base* base, const uint16_t& index, QListWidget* listWidget) :
    QWidget(parent),
    ui(new Ui::PolynomialManage)
{
    ui->setupUi(this);

    this->base = base;
    this->index = index;
    this->listWidget = listWidget;

    Functions func;
    Polynomial* p = this->base->data;
    for (uint i = 0; i < this->index; ++i) {
        p = p->next;
    }
    ui->lineEdit->setText(func.polynomialToText(p));
    ui->lineEdit_2->setText(func.polynomialToText(p));
}

PolynomialManage::~PolynomialManage()
{
    delete ui;
}

void PolynomialManage::on_pushButton_clicked()
{
    Polynomial* p = this->base->data;
    Polynomial* prev = nullptr;
    for (uint8_t i = 0; i < this->index; ++i) {
        prev = p;
        p = p->next;
    }

    if (prev == nullptr) {
        base->data = p->next;
    }
    else {
        prev->next = p->next;
    }
    delete p;
    Functions func;
    func.updateList(this->listWidget, base);
    PolynomialManage::~PolynomialManage();
    return;
}

