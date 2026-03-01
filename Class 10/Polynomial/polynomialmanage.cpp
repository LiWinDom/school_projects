#include "polynomialmanage.h"
#include "ui_polynomialmanage.h"

PolynomialManage::PolynomialManage(QWidget *parent, Base* base, const uint16_t& index, QListWidget* listWidget, QListWidget* listWidget_2) :
    QWidget(parent),
    ui(new Ui::PolynomialManage)
{
    ui->setupUi(this);

    this->base = base;
    this->index = index;
    this->listWidget = listWidget;
    this->listWidget_2 = listWidget_2;

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
    func.updateList(this->listWidget_2, base);
    PolynomialManage::~PolynomialManage();
    return;
}


void PolynomialManage::on_pushButton_4_clicked()
{
    try {
        Functions func;
        Polynomial* plc = func.textToPolynomial(ui->lineEdit_2->text().toLower());
        func.addPolynomial(base, plc);
        func.updateList(this->listWidget, base);
        func.updateList(this->listWidget_2, base);
        this->PolynomialManage::~PolynomialManage();
    }  catch (Error* err) {
        ui->label->setText(err->type + " error: " + err->descr);
        delete err;
    }
    return;
}


void PolynomialManage::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->label->setText("");
}


void PolynomialManage::on_pushButton_2_clicked()
{
    try {
        Functions func;
        Polynomial* plc = func.textToPolynomial(ui->lineEdit_2->text().toLower());
        Polynomial* p = this->base->data;
        Polynomial* prev = nullptr;
        for (uint8_t i = 0; i < index; ++i) {
            prev = p;
            p = p->next;
        }
        plc->next = p->next;
        if (prev == nullptr) {
            this->base->data = plc;
        }
        else {
            prev->next = plc;
        }
        delete p;
        func.updateList(this->listWidget, base);
        func.updateList(this->listWidget_2, base);
        this->PolynomialManage::~PolynomialManage();
    }  catch (Error* err) {
        ui->label->setText(err->type + " error: " + err->descr);
        delete err;
    }
}


void PolynomialManage::on_lineEdit_2_returnPressed()
{
    PolynomialManage::on_pushButton_4_clicked();
}


void PolynomialManage::on_pushButton_3_clicked()
{
    Polynomial* p = this->base->data;
    for (uint16_t i = 0; i < this->index; ++i) {
        p = p->next;
    }

    Functions func;
    Polynomial* der = func.der(p, ui->comboBox->currentIndex());
    for (uint8_t i = 1; i < ui->spinBox->value(); ++i) {
        Polynomial* cur = func.der(der, ui->comboBox->currentIndex());
        delete der;
        der = cur;

    }
    ui->lineEdit_2->setText(func.polynomialToText(der));
    delete der;
    return;
}


void PolynomialManage::on_pushButton_6_clicked()
{
    ui->lineEdit_2->setText(ui->lineEdit->text());
}


void PolynomialManage::on_pushButton_5_clicked()
{
    try {
        Functions func;
        // Check
        QString last = "start";
        QString text = ui->lineEdit_3->text().toLower();
        for (uint8_t i = 0; i < text.size(); ++i) {
            if (last == "start") {
                if (text[i] == ' ') {
                    continue;
                }
                if (text[i] >= 'a' && text[i] <= 'z') {
                    last = "letter";
                    continue;
                }
            }
            if (last == "letter") {
                if (text[i] == ' ') {
                    continue;
                }
                if (text[i] == '=') {
                    last = "=";
                    continue;
                }
                if (text[i] >= '0' && text[i] <= '9') {
                    last = "number";
                }
            }
            if (last == "=") {
                if (text[i] == ' ') {
                    continue;
                }
                if (text[i] >= '0' && text[i] <= '9') {
                    last = "number";
                    continue;
                }
            }
            if (last == "number") {
                if (text[i] == ' ') {
                    last = "numSpace";
                    continue;
                }
                if (text[i] >= 'a' && text[i] <= 'z') {
                    last = "letter";
                    continue;
                }
                if (text[i] >= '0' && text[i] <= '9') {
                    last = "number";
                    continue;
                }
            }
            if (last == "numSpace") {
                if (text[i] == ' ') {
                    continue;
                }
                if (text[i] >= 'a' && text[i] <= 'z') {
                    last = "letter";
                    continue;
                }
                if (text[i] == ';') {
                    last = ";";
                    continue;
                }
            }
            if (last == ";") {
                if (text[i] == ' ') {
                    continue;
                }
                if (text[i] >= 'a' && text[i] <= 'z') {
                    last = "letter";
                    continue;
                }
            }
            throw new Error("Input", QString::fromStdString("Unexpected \"") + text[i] + QString::fromStdString("\" at position ") + QString::number(i + 1));
        }
        if (last == "start") {
            throw new Error("Input", "You should white something");
        }
        if (last == "letter" || last == "=") {
            throw new Error("Input", "Unexpected end of expression");
        }
    }  catch (Error* err) {
        ui->label->setText(err->type + " error: " + err->descr);
        delete err;
        return;
    }

    Polynomial* plc = base->data;
    for (uint16_t i = 0; i < this->index; ++i) {
        plc = plc->next;
    }
    Polynomial* newPlc = new Polynomial;

    int16_t num = 0;
    uint8_t letter = 0;
    QString last = "start";
    std::string text = ui->lineEdit_3->text().toLower().replace(" ", "").replace("=", "").replace(";", "").toStdString();
    for (uint8_t i = 0; i < text.size(); ++i) {
        if (last == "start") {
            if (text[i] >= 'a' && text[i] <= 'z') {
                last = "letter";
                letter = text[i] - 'a';
                continue;
            }
        }
        if (last == "letter") {
            if (text[i] >= '0' && text[i] <= '9') {
                last = "number";
                num = num * 10 + (text[i] & 15);
                continue;
            }
        }
        if (last == "number") {
            if (text[i] >= 'a' && text[i] <= 'z') {
                Segment* sg = plc->data;
                while (sg != nullptr) {
                    int16_t mult = std::pow(num, sg->deg[letter]);
                    sg->coef *= mult;
                    sg = sg->next;
                }

                last = "letter";
                letter = text[i] - 'a';
                num = 0;
                continue;
            }
            if (text[i] >= '0' && text[i] <= '9') {
                num = num * 10 + (text[i] & 15);
                continue;
            }
        }
    }
    Segment* sg = plc->data;
    while (sg != nullptr) {
        int16_t mult = std::pow(num, sg->deg[letter]);
        sg->coef *= mult;
        sg = sg->next;
    }
    return;
}


void PolynomialManage::on_lineEdit_3_textChanged(const QString &arg1)
{
    PolynomialManage::on_lineEdit_2_textChanged("");
}


void PolynomialManage::on_lineEdit_3_returnPressed()
{
    PolynomialManage::on_pushButton_5_clicked();
}

