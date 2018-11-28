#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onNewTextEntered(const QString &text)
{
    // Adding a new item to the list widget
    ui->myListWidget->addItem(text);
    qDebug() << "je suis un baguette";
}
