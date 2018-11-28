#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow first;
    Dialog second;

    // Connecting the signal we created in the first form
    // with the slot created in the second form
    QObject::connect(&first, SIGNAL(newTextEntered(const QString&)),
                     &second, SLOT(onNewTextEntered(const QString&)));
    QObject::connect(&first, SIGNAL(newCustomTextEntered(const QString&)),
                     &second, SLOT(onNewTextEntered(const QString&)));

    // Showing them
    first.show();
    second.show();
    
    return a.exec();
}
