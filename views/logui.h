#ifndef LOGUI_H
#define LOGUI_H

#include <QDialog>

namespace Ui {
class logui;
}

class logui : public QDialog
{
    Q_OBJECT

public:
    explicit logui(QWidget *parent = nullptr);
    static logui* get_logui();
    ~logui();
public slots:
    void on_write_update_logui             ( QString data);
private:
    Ui::logui *ui;
signals:
    /*signal call output*/
    void on_request_update_logui           ( QString data);
//protected:
//    void closeEvent(QCloseEvent *event);
};
void update_data_logui(QString data);
#endif // LOGUI_H
