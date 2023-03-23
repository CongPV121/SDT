#ifndef PMU_H
#define PMU_H

#include <QDockWidget>

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

private:
    Ui::pmu *ui;
    void parse_data(const QString& data);
};

#endif // PMU_H
