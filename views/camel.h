#ifndef CAMEL_H
#define CAMEL_H

#include <QDialog>

namespace Ui {
class camel;
}

class camel : public QDialog
{
    Q_OBJECT

public:
    explicit camel(QWidget *parent = nullptr);
    static camel* get_camel();
    QString get_link_director() const ;
    bool warning_success;
    void set_link_director(const QString& link_director);    ~camel();
public slots:
    void percents_to_complete                   (const int& percent);
    void on_write_write_fw_button               (int value );
private slots:
    void on_connect_dut_clicked();

    void on_deviceList_currentIndexChanged(int index);

    void on_write_fw_clicked();

private:
    Ui::camel *ui;
    QString link_director;
    void parse_data(const QString& data);
signals:
        /*call signal connect(hmi::get_hmi, &hmi::<signal>, this,&<localLib>::<local_slot>)*/
        /*signal call output*/
        void on_request_write_firmware          (const QUrl& url); //write firm ware to module
        /*signal call input*/
        /*call  connect(hmi::get_hmi, &hmi::<signal>, this,&<localLib>::<local_slot>)*/
        void on_response_percents_to_complete   (const int& percent); //percent download code
        void on_response_write_fw_button                 (int value);
//protected:
//    void closeEvent(QCloseEvent *event);

};
void set_value_processbar_camel(const int value, uint8_t state_process);

#endif // CAMEL_H
