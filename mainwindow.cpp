#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QProcess"
#include <QListWidgetItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStringListModel(this);

    connect(ui->pushBtn, SIGNAL(clicked()), this, SLOT(ClickButton()));

    this->getAndroidEmulators();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getAndroidEmulators() {
    QProcess *myProcess = new QProcess(this);
    QString program = "emulator";
    QStringList arguments;
    arguments<<"-list-avds";
    myProcess->start(program, arguments);

    if(!myProcess->waitForStarted())
        return;

    myProcess->write("Qt rocks");
    myProcess->closeWriteChannel();

    if(!myProcess->waitForFinished())
        return;

    QByteArray result = myProcess->readAll();
    QString sresult = result;

    // Make data
    List = sresult.split("\n", QString::SkipEmptyParts);
//    List << "Clair de Lune" << "Reverie" << "Prelude";

    // Populate our model
    model->setStringList(List);

    ui->listView->setModel(model);
}

void MainWindow::ClickButton() {
    QStringList list;
    QString selected;
    foreach(const QModelIndex &index, ui->listView->selectionModel()->selectedIndexes()) {
       int row = index.row();
       QString item = this->List.at(row);
       selected = item;
       selected.remove(QChar('\r'));
       break;
    }
    qDebug()<<selected;

    QProcess *myProcess = new QProcess(this);
    QString program = "emulator";
    QStringList arguments;
    arguments<<"-avd"<<selected;
    myProcess->setWorkingDirectory("D:/Android/Sdk/emulator/");

    myProcess->start(program, arguments);

    if(!myProcess->waitForStarted(2000))
        return;

    myProcess->closeWriteChannel();

    if(!myProcess->waitForFinished(2000))
        return;

    QString result = myProcess->readAll();
    QString error = myProcess->readAllStandardError();

    qDebug()<<"Result: "<<result<<"; Error: "<<error;

    QString final;
    if(result.isEmpty()) {
        final = error;
    } else {
        final = result;
    }

    QMessageBox::information(NULL, "Title", final, QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
}
