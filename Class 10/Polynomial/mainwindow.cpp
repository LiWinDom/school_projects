#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exit()));

    connect(ui->actionLight, SIGNAL(triggered()), this, SLOT(setLight()));
    connect(ui->actionDark, SIGNAL(triggered()), this, SLOT(setDark()));

    ui->actionLight->setChecked(true);

    ui->actionLight->setDisabled(true);
    ui->actionDark->setDisabled(true);

    ui->lineEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    MainWindow::~MainWindow();
}

void MainWindow::setLight()
{
    ui->actionLight->setChecked(true);
    ui->actionDark->setChecked(false);
}

void MainWindow::setDark()
{
    ui->actionLight->setChecked(false);
    ui->actionDark->setChecked(true);
}

void MainWindow::on_pushButton_clicked()
{
    try {
        Functions func;
        Polynomial* plc = func.textToPolynomial(ui->lineEdit->text().toLower());
        func.addPolynomial(base, plc);
        func.updateList(ui->listWidget, base);
        func.updateList(ui->listWidget_2, base);
        ui->lineEdit->setText("");
    }  catch (Error* err) {
        ui->statusbar->showMessage(err->type + " error: " + err->descr);
        delete err;
    }
    return;
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    this->w = new PolynomialManage(nullptr, base, ui->listWidget->currentRow(), ui->listWidget, ui->listWidget_2);
    w->show();
}


void MainWindow::on_lineEdit_returnPressed()
{
    MainWindow::on_pushButton_clicked();
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->statusbar->showMessage("", 1);
}


void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    this->w = new PolynomialManage(nullptr, base, ui->listWidget_2->currentRow(), ui->listWidget, ui->listWidget_2);
    w->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (ui->listWidget->currentRow() == -1) {
        ui->statusbar->showMessage("Nothing selected at 1 list");
        return;
    }
    if (ui->listWidget_2->currentRow() == -1) {
        ui->statusbar->showMessage("Nothing selected at 2 list");
        return;
    }
    ui->statusbar->showMessage("");
    Functions func;
    Polynomial* plc1 = base->data, *plc2= base->data;
    for (uint16_t i = 0; i < ui->listWidget->currentRow(); ++i) {
        plc1 = plc1->next;
    }
    for (uint16_t i = 0; i < ui->listWidget_2->currentRow(); ++i) {
        plc2 = plc2->next;
    }
    Polynomial* sum = func.sum(plc1, plc2);
    ui->lineEdit->setText(func.polynomialToText(sum));
    delete sum;
    return;
}


void MainWindow::on_pushButton_3_clicked()
{
    if (ui->listWidget->currentRow() == -1) {
        ui->statusbar->showMessage("Nothing selected at 1 list");
        return;
    }
    if (ui->listWidget_2->currentRow() == -1) {
        ui->statusbar->showMessage("Nothing selected at 2 list");
        return;
    }
    ui->statusbar->showMessage("");
    Functions func;
    Polynomial* plc1 = base->data, *plc2= base->data;
    for (uint16_t i = 0; i < ui->listWidget->currentRow(); ++i) {
        plc1 = plc1->next;
    }
    for (uint16_t i = 0; i < ui->listWidget_2->currentRow(); ++i) {
        plc2 = plc2->next;
    }
    Polynomial* mult = func.mult(plc1, plc2);
    ui->lineEdit->setText(func.polynomialToText(mult));
    delete mult;
    return;
}

