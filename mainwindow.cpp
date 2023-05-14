#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_list_listwidget() {
    QList<QString> strings;
    for(int i : this->list) {
        strings.append(QString::fromStdString(to_string(i)));
    }

    ui->arraylist_listwidget->clear();
    ui->arraylist_listwidget->insertItems(0, strings);

    ui->datasetsizedisplay_label->setText("The dataset size is: " + QString::number(this->list.size()));
}

void MainWindow::refresh_search_method() {
    ui->usingsearch_label->setText(QString::fromStdString("Searching with: " + search_method_strings[this->search_method] + " Search"));
}


void MainWindow::on_generatedataset_pb_clicked()
{
    // Get text from the qtextedit called "datasetsize_te" and generate an array with the number of elements mathcing the text in the qtextedit
    QString datasetSizeText = ui->datasetsize_te->toPlainText();
    int datasetSize = datasetSizeText.toInt();
    // cout << datasetSize << endl;
    srand(time(NULL));
    this->list.clear();
    for (int i = 0; i < datasetSize; i++) {
        this->list.push_back(rand() % 1000);
    }

    refresh_list_listwidget();
}


void MainWindow::on_normalsearch_pb_clicked()
{
    this->search_method = SearchMethod::Normal;
    this->refresh_search_method();
}


void MainWindow::on_binarysearch_pb_clicked()
{
    this->search_method = SearchMethod::Binary;
    this->refresh_search_method();
}

