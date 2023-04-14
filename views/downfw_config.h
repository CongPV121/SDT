#ifndef DOWNFW_CONFIG_H
#define DOWNFW_CONFIG_H

#include <QDialog>

namespace Ui {
class downfw_config;
}

class downfw_config : public QDialog
{
    Q_OBJECT

public:
    explicit    downfw_config(QWidget *parent = nullptr);
    static      downfw_config* get_downfw_config();
    void        showFwConfigList();
    int         saveConfigPara(QString destFilePath);
    void        updateListFwDevice(QString destFilePath, QString nameDevice,
                                   QString codeDevice, QString linkFile ,
                                   QString version );
    ~downfw_config();

private slots:
    void on_pushButton_clicked();

    void on_codeDevice_activated(int index);

    void on_linkFile_clicked();

    //void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_cellPressed(int row, int column);

private:
    Ui::downfw_config *ui;
    QString linkFile;
};
int     copyFile        (QString sourceFilePath, QString destFilePath );
void    getFwConfigList (QString srcPath);
void    FwConfigListInit();



#endif // DOWNFW_CONFIG_H
