#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
      //      this, SLOT(openNewWindow()));
    Filename ="D:/Test/Myxml.xml";
    model = new QStandardItemModel(0,1,this);
    ReadFile();
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
    qDebug() << "Close event";
    for(int i=0; i<dialogs.length(); i++){
        qDebug() << "Close it";
        dialogs[i]->close();
    }
}


void MainWindow::openNewWindow()
{
    //independent window
    myNewWindow = new Dialog();
    //myNewWindow = new Dialog(this);
    myNewWindow ->show();
    dialogs.append(myNewWindow);
    //Goes on top of mainwindow.
    /*Dialog d;
    d.setModal(false);
    d.exec();*/
    //This wont work it will blink
    /*Dialog d;
    d.window();
    d.show();*/
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    openNewWindow();
    /*if(ui->listWidget->currentItem()->text()=="New Window"){
        openNewWindow();
    }
    else{
        ui->listWidget_2->addItem(ui->listWidget->currentItem()->clone());
    }*/
}

void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    delete ui->listWidget_2->currentItem();
}

void MainWindow::on_pushButton_clicked()
{
    //WriteFile();
}

void MainWindow::WriteFile()
{
    //write the xml file

    QDomDocument document;

    //Make a root node
    QDomElement xmlroot = document.createElement("Books");
    document.appendChild(xmlroot);

    QStandardItem *root = model->item(0,0); //tager den eksisterende model. Og initialisere rooten, som altid er 0,0
    for(int i=0; i<root->rowCount();i++){
        QStandardItem *book = root->child(i,0);

        QDomElement xmlbook = document.createElement("Book");
        xmlbook.setAttribute("Name", book->text());
        xmlbook.setAttribute("ID", i);
        xmlroot.appendChild(xmlbook);

        for(int h=0; h<book->rowCount(); h++){
            QStandardItem *chapter = book->child(h,0);
            QDomElement xmlchapter = document.createElement("Chapter");

            xmlchapter.setAttribute("Name", chapter->text());
            xmlchapter.setAttribute("ID", h);
            xmlbook.appendChild(xmlchapter);
        }
    }
    QFile file(Filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "Failed to write file";
    }
    else{
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Finished";
    }

    ReadFile(); //lige genindlæse filen
}


void MainWindow::ReadFile()
{

    QStandardItem *root = new QStandardItem("Books");
    model->appendRow(root);

    QDomDocument document;

    //Load the xml file
    QFile file(Filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        document.setContent(&file);
        file.close();
    }

    //get the xml root element
    QDomElement xmlroot = document.firstChildElement();

    //read the books

    QDomNodeList books = xmlroot.elementsByTagName("Book");
    for(int i=0;i<books.count();i++){ //for antal elementer i root
        QDomElement book = books.at(i).toElement();
        QStandardItem *bookitem = new QStandardItem(book.attribute("Name"));

        //Read the chapters of the book
           QDomNodeList chapters = xmlroot.elementsByTagName("Chapter");
           for(int h=0; h<chapters.count(); h++){ //for antal chapters i den nylig lavet nodelist
               QDomElement chapter = chapters.at(h).toElement();
               QStandardItem *chapteritem = new QStandardItem(chapter.attribute("Name"));

               bookitem->appendRow(chapteritem); //Så får bookitemet tilføjet den tilsvarende chapter element
           }
           root->appendRow(bookitem);
    }

}
