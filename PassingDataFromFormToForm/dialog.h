#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    QString x;
    ~Dialog();

public slots:
    void onNewTextEntered(const QString &text);
    
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
