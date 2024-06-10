#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QStandardPaths"
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(path);

    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file(path);

    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream out(&file);

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        out << ui->listWidget->item(i)->text() << "\n";
    }

    file.close();
}

bool noContent(QString s) {
    if (s.isEmpty())
        return true;
    for (int i = 0; i < s.size(); i++)
        if (s[i] != ' ')
            return false;
    return true;
}

void MainWindow::on_btnAdd_clicked()
{
    QListWidgetItem* item = new QListWidgetItem(ui->txtTask->text(), ui->listWidget);
    ui->txtTask->clear();
    ui->txtTask->setFocus();
    if (noContent(item->text())) {
        delete item;
        return;
    }
    ui->listWidget->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}


void MainWindow::on_btnRemove_clicked()
{
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}


void MainWindow::on_btnRemoveAll_clicked()
{
    ui->listWidget->clear();
}

