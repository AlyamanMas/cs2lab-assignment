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

namespace util {
    bool check_if_sorted(vector<int> vec) {
        for (int i = 0; i < vec.size() - 1; i++) {
            if (vec[i] > vec[i + 1]) {
                return false;
            }
        }
        return true;
    }
    void merge_sort(vector<int> &vec) {
        if (vec.size() <= 1) {
            return;
        }
        int middle = vec.size() / 2;
        vector<int> left(vec.begin(), vec.begin() + middle);
        vector<int> right(vec.begin() + middle, vec.end());
        merge_sort(left);
        merge_sort(right);
        vector<int> result;
        int left_index = 0;
        int right_index = 0;
        while (left_index < left.size() && right_index < right.size()) {
            if (left[left_index] < right[right_index]) {
                result.push_back(left[left_index]);
                left_index++;
            } else {
                result.push_back(right[right_index]);
                right_index++;
            }
        }
        while (left_index < left.size()) {
            result.push_back(left[left_index]);
            left_index++;
        }
        while (right_index < right.size()) {
            result.push_back(right[right_index]);
            right_index++;
        }
        vec = result;
    }
}

void MainWindow::refresh_list_listwidget() {
    QList<QString> strings;
    for(int i : this->list) {
        strings.append(QString::fromStdString(to_string(i)));
    }

    ui->arraylist_listwidget->clear();
    ui->arraylist_listwidget->insertItems(0, strings);

    ui->datasetsizedisplay_label->setText("The dataset size is: " + QString::number(this->list.size()));

    if (util::check_if_sorted(this->list)) {
        ui->sortedornot_label->setText("Sorted!");
    } else {
        ui->sortedornot_label->setText("Not Sorted :(");
    }
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


void MainWindow::on_mergesort_pb_clicked()
{
    ui->sortedusing_label->setText("Sorting Using: Merge Sort");

    util::merge_sort(this->list);
    this->refresh_list_listwidget();
}


void MainWindow::on_stlsort_pb_clicked()
{
    ui->sortedusing_label->setText("Sorting Using: STL Sort");

    std::sort(this->list.begin(), this->list.end());
    this->refresh_list_listwidget();
}

