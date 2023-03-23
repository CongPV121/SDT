#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "views/pmu.h"
#include "views/hmi.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:    
    void on_testBpButton_clicked();

    void on_testPmuButton_clicked();

    void on_testHmiButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
