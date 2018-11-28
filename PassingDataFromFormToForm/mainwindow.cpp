#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //really not necessary. Rookie mistake. Use slots from forms ui.
    //connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SIGNAL(on_lineEdit_returnPressed())); //eller SIGNAL(on_pushButton_clicked())
    //connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SIGNAL(newCustomTextEntered(QString))); //eller SIGNAL(on_pushButton_clicked())
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_returnPressed()
{
    emit this->newTextEntered(ui->lineEdit->text());
    emit this->newCustomTextEntered("dank "+ui->lineEdit->text());
}

void MainWindow::on_pushButton_clicked()
{
    on_lineEdit_returnPressed();
}

