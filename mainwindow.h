#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef enum {
    Binary,
    Normal
} SearchMethod;

const std::string search_method_strings[] = {
    "Binary",
    "Normal"
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generatedataset_pb_clicked();

    void on_normalsearch_pb_clicked();

    void on_binarysearch_pb_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<int> list;
    SearchMethod search_method = SearchMethod::Binary;

    void refresh_list_listwidget();
    void refresh_search_method();
};
#endif // MAINWINDOW_H
