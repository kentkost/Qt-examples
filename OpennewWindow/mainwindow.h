#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <dialog.h>
#include <QtXml>
#include <QDebug>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QList<Dialog *> dialogs;
    ~MainWindow();

    
private slots:

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void closeEvent(QCloseEvent *event);
    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_clicked();

public slots:
    void openNewWindow();

private:
    Ui::MainWindow *ui;
    Dialog *myNewWindow;
    QStandardItemModel *model;
    QString Filename;
    void ReadFile();
    void WriteFile();

};

#endif // MAINWINDOW_H
