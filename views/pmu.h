#ifndef PMU_H
#define PMU_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
/*-------------------------Dialog*/
class MyDialog : public QDialog
{
public:
    MyDialog(QWidget *parent = nullptr)
        : QDialog(parent)
    {
        // Tạo các phần tử UI
        QLabel *label = new QLabel(tr("Enter your name:"));
        QLineEdit *lineEdit = new QLineEdit;
        QPushButton *okButton = new QPushButton(tr("OK"));
        QPushButton *cancelButton = new QPushButton(tr("Cancel"));

        // Định vị trí các phần tử UI bằng layout
        QVBoxLayout *mainLayout = new QVBoxLayout;
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        mainLayout->addWidget(label);
        mainLayout->addWidget(lineEdit);
        mainLayout->addLayout(buttonLayout);
        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        // Kết nối các phần tử UI với các chức năng tương ứng
        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        // Cấu hình dialog
        setLayout(mainLayout);
        setWindowTitle(tr("My Dialog"));
    }
};
//
namespace Ui {
class pmu;
}

class pmu : public QDockWidget
{
    Q_OBJECT

public:
    explicit pmu(QWidget *parent = 0);
    ~pmu();
public slots:
    void data_read_config(const QString& data);
signals:
/*signal call output*/
    void on_request_write_data_config(const QString& data);
    void on_request_write_firmware(const QUrl& url);
    void on_request_read_data_config(const QString& module);
/*signal call input*/
    void on_response_percents_to_complete(const int& percent);
    void on_response_read_data_config(const QString&data);
private slots:
    void on_read_btn_clicked();
    void on_write_btn_clicked();

    void on_write_firm_ware_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_new_test_clicked();

private:
    Ui::pmu *ui;
    void parse_data(const QString& data);
//protected:
//    void closeEvent(QCloseEvent *event);
};

#endif // PMU_H
