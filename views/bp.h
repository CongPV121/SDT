#ifndef BP_H
#define BP_H

#include <QDialog>

namespace Ui {
class bp;
}

class bp : public QDialog
{
    Q_OBJECT

public:
    explicit bp(QWidget *parent = nullptr);
    static bp* get_bp();
    QString get_link_director() const ;
    void set_link_director(const QString& link_director);
    ~bp();

private slots:
    void on_choose_file_btn_clicked();

    void on_write_firm_ware_clicked();

private:
    Ui::bp *ui;
    QString link_director;
    void parse_data(const QString& data);
signals:
    /*call signal connect(hmi::get_hmi, &hmi::<signal>, this,&<localLib>::<local_slot>)*/
    /*signal call output*/
    void on_request_write_data_config       (const QString& data); //write data config to module
    void on_request_write_firmware          (const QUrl& url); //write firm ware to module
    void on_request_read_data_config        (const QString& module); //connect to module
    /*signal call input*/
    /*call  connect(hmi::get_hmi, &hmi::<signal>, this,&<localLib>::<local_slot>)*/
    void on_response_percents_to_complete   (const int& percent); //percent download code
    void on_response_read_data_config       (const QString&data); // data config
    void on_response_read_serial_number     (const QString&data);
    void on_response_read_fw_version        (const QString&data);
    void on_response_read_hw_version        (const QString&data);
    void on_response_read_esim_number       (const QString&data);
};
void set_value_processbar_bp(const int value, uint8_t state_process);

#endif // BP_H
