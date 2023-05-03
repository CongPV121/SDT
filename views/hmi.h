#ifndef HMI_H
#define HMI_H

#include <QDialog>

namespace Ui {
class hmi;
}

class hmi : public QDialog
{
    Q_OBJECT

public:
    explicit hmi(QWidget *parent = 0);
    static hmi* get_hmi();
    QString get_link_director() const ;
    bool warning_success;
    void set_link_director(const QString& link_director);
    ~hmi();
public slots:
    void data_read_config               (const QString& data);
    void percents_to_complete           (const int& percent); //percent download code
    void on_write_serial_number         (QString value);
    void on_write_fw_version            (QString value);
    void on_write_hw_version            (QString value);
    void on_write_esim_number           (QString value);
    void on_write_write_fw_button       (int value);

private slots:
    void on_read_btn_clicked();
    void on_write_btn_clicked();

    void on_write_firm_ware_clicked();

    void on_choose_file_btn_clicked();

    void on_write_process_valueChanged  (int value);

    void on_connect_dut_clicked();

    void on_read_btn_2_clicked();

    void on_connect_dut_2_clicked();

    void on_write_config_clicked();

private:
    Ui::hmi *ui;
    QString link_director;
    void parse_data(const QString& data);

    /*implement for user*/
    //-----------------------------------------------------------------------------------------------------
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
        void on_response_write_fw_button                 (int value);
//protected:
//    void closeEvent(QCloseEvent *event);

};
void setText_ev_id      (const char* value);
void setText_esim_number        (const char* value);
void setText_hw_version         (const char* value);
void setText_fw_version         (const uint8_t* value);
void set_value_processbar(const int value, uint8_t state_process);

#endif // HMI_H
