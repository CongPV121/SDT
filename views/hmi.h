#ifndef HMI_H
#define HMI_H

#include <QDockWidget>

namespace Ui {
class hmi;
}

class hmi : public QDockWidget
{
    Q_OBJECT

public:
    explicit hmi(QWidget *parent = 0);
    static hmi* get_hmi();
    QString get_link_director() const ;
    void set_link_director(const QString& link_director);
    ~hmi();
public slots:
    void data_read_config(const QString& data);
    void percents_to_complete(const int& percent); //percent download code

private slots:
    void on_read_btn_clicked();
    void on_write_btn_clicked();

    void on_write_firm_ware_clicked();

    void on_choose_file_btn_clicked();

    void on_write_process_valueChanged(int value);

private:
    Ui::hmi *ui;
    QString link_director;
    void parse_data(const QString& data);


/*implement for user*/
//-----------------------------------------------------------------------------------------------------
signals:
    /*call signal connect(hmi::get_hmi, &hmi::<signal>, this,&<localLib>::<local_slot>)*/
    /*signal call output*/
    void on_request_write_data_config(const QString& data); //write data config to module
    void on_request_write_firmware(const QUrl& url); //write firm ware to module
    void on_request_read_data_config(const QString& module); //connect to module
    /*signal call input*/
    /*call  connect(hmi::get_hmi, &hmi::<signal>, this,&<localLib>::<local_slot>)*/
    void on_response_percents_to_complete(const int& percent); //percent download code
    void on_response_read_data_config(const QString&data); // data config
//-----------------------------------------------------------------------------------------------------
};

#endif // hmi_H
