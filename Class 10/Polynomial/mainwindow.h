#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "classes.h"
#include "functions.h"
#include "polynomialmanage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Q_SLOT void exit();

    Q_SLOT void setLight();

    Q_SLOT void setDark();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_lineEdit_returnPressed();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    Base* base = new Base;

    PolynomialManage* w = nullptr;
};
#endif // MAINWINDOW_H
