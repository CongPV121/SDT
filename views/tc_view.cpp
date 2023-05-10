#include "testing_config.h"
#include "ui_testing_config.h"
#include <QMessageBox>
#include "Controller/testing/testing.h"
#include "Controller/testing/testcase/testcase.h"
#include <QtGui/QIntValidator>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Controller/config/config.h"


/*----------------Show config test case-------------------------*/
void config_dialog::set_dialog_TC_DUT_IO1(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);
    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);
    QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);
    QLabel *correct_level_label         = new QLabel("Correct Level:", this);

    QLineEdit *timeout_ms_edit          = new QLineEdit(this);
    QLineEdit *dut_tc_id_edit           = new QLineEdit( this);
    QLineEdit *correct_level_edit       = new QLineEdit( this);


    timeout_ms_edit->setValidator(new QIntValidator(0, 999999,timeout_ms_edit ));
    dut_tc_id_edit->setValidator(new QIntValidator(0, 255, dut_tc_id_edit));
    correct_level_edit->setValidator(new QIntValidator(0, 255, correct_level_edit));

    timeout_ms_edit->setObjectName("timeout_ms");
    dut_tc_id_edit->setObjectName("dut_tc_id");
    correct_level_edit->setObjectName("correct_level");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = this->row_continue;
    gridLayout->addWidget(timeout_ms_label,     row++, 0);
    gridLayout->addWidget(dut_tc_id_label,      row++, 0);
    gridLayout->addWidget(correct_level_label,  row++, 0);

    row = this->row_continue;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,       row++, 1);
    gridLayout->addWidget(correct_level_edit,   row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();
}



void config_dialog::set_dialog_TC_DUT_IO2(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_DUT_IO3(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);

    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);
    QLabel *io_output_x_channel_label   = new QLabel("IO Channel:", this);
    QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);

    QLineEdit *timeout_ms_edit             = new QLineEdit(this);
    QLineEdit *io_output_x_channel_edit    = new QLineEdit( this);
    QLineEdit *dut_tc_id_edit              = new QLineEdit( this);

    timeout_ms_edit->setObjectName("timeout_ms");
    dut_tc_id_edit->setObjectName("dut_tc_id");
    io_output_x_channel_edit->setObjectName("io_output_x_channel");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = this->row_continue;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(io_output_x_channel_label,    row++, 0);
    gridLayout->addWidget(dut_tc_id_label,    row++, 0);

    row = this->row_continue;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(io_output_x_channel_edit,    row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,    row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1,     Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();

}
void config_dialog::set_dialog_TC_JIG_IO1(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_JIG_IO2(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_JIG_IO3(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_JIG_IO4(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_JIG_IO5(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);
    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);
    QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);
    QLabel *io_input_y_channel_label    = new QLabel("IO Input y channel:", this);

    QLineEdit *timeout_ms_edit              = new QLineEdit(this);
    QLineEdit *io_input_y_channel_edit      = new QLineEdit( this);
    QLineEdit *dut_tc_id_edit               = new QLineEdit( this);

    timeout_ms_edit->setValidator(new QIntValidator(0, 999999,timeout_ms_edit ));
    io_input_y_channel_edit->setValidator(new QIntValidator(0, 999999, io_input_y_channel_edit));;
    dut_tc_id_edit->setValidator(new QIntValidator(0, 999999, dut_tc_id_edit));

    timeout_ms_edit->setObjectName("timeout_ms");
    io_input_y_channel_edit->setObjectName("io_input_y_channel");
    dut_tc_id_edit->setObjectName("dut_tc_id");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = this->row_continue;
    gridLayout->addWidget(timeout_ms_label,                 row++, 0);
    gridLayout->addWidget(io_input_y_channel_label,         row++, 0);
    gridLayout->addWidget(dut_tc_id_label,                  row++, 0);
    row = this->row_continue;
    gridLayout->addWidget(timeout_ms_edit,                  row++, 1);
    gridLayout->addWidget(io_input_y_channel_edit,         row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,                   row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();
}
void config_dialog::set_dialog_TC_JIG_IO6(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_JIG_IO7(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);
    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);

    QLabel *io_output_x_channel_label  = new QLabel("io_output_x_channel:", this);
    QLabel *io_output_y_channel_label   = new QLabel("io_output_y_channel:", this);
    QLabel *io_input_z_channel_label    = new QLabel("io_input_z_channel:", this);
    QLabel *io_output_x_lv_label       = new QLabel("io_output_x_lv:", this);

    QLineEdit *timeout_ms_edit    = new QLineEdit(this);
    QLineEdit *io_output_x_channel_edit     = new QLineEdit(this);
    QLineEdit *io_output_y_channel_edit   = new QLineEdit( this);
    QLineEdit *io_input_z_channel_edit    = new QLineEdit( this);
    QLineEdit *io_output_x_lv_edit     = new QLineEdit( this);

    timeout_ms_edit->setValidator(new QIntValidator(0, 999999,timeout_ms_edit ));
    io_output_x_channel_edit->setValidator(new QIntValidator(0, 255, io_output_x_channel_edit));
    io_output_y_channel_edit->setValidator(new QIntValidator(0, 255, io_output_y_channel_edit));
    io_input_z_channel_edit->setValidator(new QIntValidator(0, 999999, io_input_z_channel_edit));
    io_output_x_lv_edit->setValidator(new QIntValidator(0, 999999, io_output_x_lv_edit));

    timeout_ms_edit->setObjectName("timeout_ms");
    io_output_x_channel_edit->setObjectName("io_output_x_channel");
    io_output_y_channel_edit->setObjectName("io_output_y_channel");
    io_input_z_channel_edit->setObjectName("io_input_z_channel");
    io_output_x_lv_edit->setObjectName("io_output_x_lv");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = this->row_continue;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(io_output_x_channel_label,      row++, 0);
    gridLayout->addWidget(io_output_y_channel_label,    row++, 0);
    gridLayout->addWidget(io_input_z_channel_label,     row++, 0);
    gridLayout->addWidget(io_output_x_lv_label,      row++, 0);

    row = this->row_continue;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(io_output_x_channel_edit,      row++, 1);
    gridLayout->addWidget(io_output_y_channel_edit,    row++, 1);
    gridLayout->addWidget(io_input_z_channel_edit,     row++, 1);
    gridLayout->addWidget(io_output_x_lv_edit,      row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();
}
void config_dialog::set_dialog_TC_JIG_VOLT1(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);
    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);

    QLabel *adcChanel_label   = new QLabel("Cổng ADC:", this);
    QLabel *adcVolt_div_label = new QLabel("Tỷ số bộ chia điện áp:", this);
    QLabel *sampleTime_label  = new QLabel("Chu kỳ lấy mẫu (ms):", this);
    QLabel *sampleNum_label   = new QLabel("Số lần trích mẫu:", this);
    QLabel *volMax_label      = new QLabel("Giá trị điện áp trung bình lớn nhất (mV):", this);
    QLabel *volMin_label      = new QLabel("Giá trị điện áp trung bình nhỏ nhất (mV):", this);
    QLabel *volDelta_label    = new QLabel("Giá trị điện áp dao động lớn nhất "
                                           "\n giữa các lần lấy mẫu (mV):", this);
    // QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);

    QLineEdit *timeout_ms_edit    = new QLineEdit(this);
    QLineEdit *adcChanel_edit     = new QLineEdit(this);
    QLineEdit *adcVolt_div_edit   = new QLineEdit( this);
    QLineEdit *sampleTime_edit    = new QLineEdit( this);
    QLineEdit *sampleNum_edit     = new QLineEdit( this);
    QLineEdit *volMax_edit        = new QLineEdit(this);
    QLineEdit *volMin_edit        = new QLineEdit( this);
    QLineEdit *volDelta_edit      = new QLineEdit( this);
    // QLineEdit *dut_tc_id_edit     = new QLineEdit( this);

    timeout_ms_edit->setValidator(new QIntValidator(0, 999999,timeout_ms_edit ));
    adcChanel_edit->setValidator(new QIntValidator(0, 255, adcChanel_edit));
    adcVolt_div_edit->setValidator(new QIntValidator(0, 255, adcVolt_div_edit));
    sampleTime_edit->setValidator(new QIntValidator(0, 999999, sampleTime_edit));
    sampleNum_edit->setValidator(new QIntValidator(0, 999999, sampleNum_edit));
    volMax_edit->setValidator(new QIntValidator(0, 999999, volMax_edit));
    volMin_edit->setValidator(new QIntValidator(0, 999999, volMin_edit));
    volDelta_edit->setValidator(new QIntValidator(0, 999999, volDelta_edit));;
    //dut_tc_id_edit->setValidator(new QIntValidator(0, 999999, dut_tc_id_edit));

    timeout_ms_edit->setObjectName("timeout_ms");
    adcChanel_edit->setObjectName("adc_channel");
    adcVolt_div_edit->setObjectName("voltage_devision_ratio_1000");
    sampleTime_edit->setObjectName("cycle_time_ms");
    sampleNum_edit->setObjectName("sample_number");
    volMax_edit->setObjectName("max_avg_volt_mv");
    volMin_edit->setObjectName("min_avg_volt_mv");
    volDelta_edit->setObjectName("ripple_volt_mv");
    //dut_tc_id_edit->setObjectName("dut_tc_id_edit");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = this->row_continue;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(adcChanel_label,      row++, 0);
    gridLayout->addWidget(adcVolt_div_label,    row++, 0);
    gridLayout->addWidget(sampleTime_label,     row++, 0);
    gridLayout->addWidget(sampleNum_label,      row++, 0);
    gridLayout->addWidget(volMax_label,         row++, 0);
    gridLayout->addWidget(volMin_label,         row++, 0);
    gridLayout->addWidget(volDelta_label,       row++, 0);
    //gridLayout->addWidget(dut_tc_id_label,      row++, 0);
    row = this->row_continue;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(adcChanel_edit,      row++, 1);
    gridLayout->addWidget(adcVolt_div_edit,    row++, 1);
    gridLayout->addWidget(sampleTime_edit,     row++, 1);
    gridLayout->addWidget(sampleNum_edit,      row++, 1);
    gridLayout->addWidget(volMax_edit,         row++, 1);
    gridLayout->addWidget(volMin_edit,         row++, 1);
    gridLayout->addWidget(volDelta_edit,       row++, 1);
    //gridLayout->addWidget(dut_tc_id_edit,      row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();

}
void config_dialog::set_dialog_TC_JIG_VOLT2(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);
    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);

    QLabel *adcChanel_label   = new QLabel("Cổng ADC:", this);
    QLabel *adcVolt_div_label = new QLabel("voltage_devision_ratio_1000:", this);
    QLabel *cycle_time_ms_label  = new QLabel("Chu kỳ lấy mẫu (ms):", this);
    QLabel *sampleNum_label   = new QLabel("Số lần trích mẫu:", this);
    QLabel *volMax_label      = new QLabel("Giá trị điện áp trung bình lớn nhất (mV):", this);
    QLabel *volMin_label      = new QLabel("Giá trị điện áp trung bình nhỏ nhất (mV):", this);
    QLabel *ripple_volt_mv_label    = new QLabel("Giá trị điện áp dao động lớn nhất "
                                                 "\n giữa các lần lấy mẫu (mV):", this);

    QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);

    QLineEdit *timeout_ms_edit    = new QLineEdit(this);
    QLineEdit *adcChanel_edit     = new QLineEdit(this);
    QLineEdit *adcVolt_div_edit   = new QLineEdit( this);
    QLineEdit *sampleTime_edit    = new QLineEdit( this);
    QLineEdit *sampleNum_edit     = new QLineEdit( this);
    QLineEdit *volMax_edit        = new QLineEdit(this);
    QLineEdit *volMin_edit        = new QLineEdit( this);
    QLineEdit *volDelta_edit      = new QLineEdit( this);
    QLineEdit *dut_tc_id_edit     = new QLineEdit( this);

    timeout_ms_edit->setValidator(new QIntValidator(0, 999999,timeout_ms_edit ));
    adcChanel_edit->setValidator(new QIntValidator(0, 255, adcChanel_edit));
    adcVolt_div_edit->setValidator(new QIntValidator(0, 255, adcVolt_div_edit));
    sampleTime_edit->setValidator(new QIntValidator(0, 999999, sampleTime_edit));
    sampleNum_edit->setValidator(new QIntValidator(0, 999999, sampleNum_edit));
    volMax_edit->setValidator(new QIntValidator(0, 999999, volMax_edit));
    volMin_edit->setValidator(new QIntValidator(0, 999999, volMin_edit));
    volDelta_edit->setValidator(new QIntValidator(0, 999999, volDelta_edit));;
    dut_tc_id_edit->setValidator(new QIntValidator(0, 999999, dut_tc_id_edit));

    timeout_ms_edit->setObjectName("timeout_ms");
    adcChanel_edit->setObjectName("adc_channel");
    adcVolt_div_edit->setObjectName("voltage_devision_ratio_1000");
    sampleTime_edit->setObjectName("cycle_time_ms");
    sampleNum_edit->setObjectName("sample_number");
    volMax_edit->setObjectName("max_avg_volt_mv");
    volMin_edit->setObjectName("min_avg_volt_mv");
    volDelta_edit->setObjectName("ripple_volt_mv");
    dut_tc_id_edit->setObjectName("dut_tc_id");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = this->row_continue;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(adcChanel_label,      row++, 0);
    gridLayout->addWidget(adcVolt_div_label,    row++, 0);
    gridLayout->addWidget(cycle_time_ms_label,    row++, 0);
    gridLayout->addWidget(sampleNum_label,      row++, 0);
    gridLayout->addWidget(volMax_label,         row++, 0);
    gridLayout->addWidget(volMin_label,         row++, 0);
    gridLayout->addWidget(ripple_volt_mv_label,       row++, 0);
    gridLayout->addWidget(dut_tc_id_label,      row++, 0);
    row = this->row_continue;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(adcChanel_edit,      row++, 1);
    gridLayout->addWidget(adcVolt_div_edit,    row++, 1);
    gridLayout->addWidget(sampleTime_edit,     row++, 1);
    gridLayout->addWidget(sampleNum_edit,      row++, 1);
    gridLayout->addWidget(volMax_edit,         row++, 1);
    gridLayout->addWidget(volMin_edit,         row++, 1);
    gridLayout->addWidget(volDelta_edit,       row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,      row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();
}
void config_dialog::set_dialog_TC_JIG_VOLT3(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_DUT_VOLT1(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);

    QLabel *timeout_ms_label   = new QLabel("Timeout:", this);
    QLabel *dut_tc_id_label     = new QLabel("Mã số bài test của DUT:", this);
    QLabel *max_avg_volt_mv_label  = new QLabel("Giá trị điện áp trung bình lớn nhất (mV):", this);
    QLabel *min_avg_volt_mv_label   = new QLabel("Giá trị điện áp trung bình nhỏ nhất (mV):", this);
    QLabel *ripple_volt_mv_label      = new QLabel("Giá trị điện áp dao động (mV):", this);


    QLineEdit *timeout_ms_edit     = new QLineEdit(this);
    QLineEdit *dut_tc_id_edit   = new QLineEdit( this);
    QLineEdit *max_avg_volt_mv_edit    = new QLineEdit( this);
    QLineEdit *min_avg_volt_mv_edit     = new QLineEdit( this);
    QLineEdit *ripple_volt_mv_edit        = new QLineEdit(this);

    timeout_ms_edit->setObjectName("timeout_ms");
    dut_tc_id_edit->setObjectName("dut_tc_id");
    max_avg_volt_mv_edit->setObjectName("max_avg_volt_mv");
    min_avg_volt_mv_edit->setObjectName("min_avg_volt_mv");
    ripple_volt_mv_edit->setObjectName("ripple_volt_mv");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = 3;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(dut_tc_id_label,    row++, 0);
    gridLayout->addWidget(max_avg_volt_mv_label,     row++, 0);
    gridLayout->addWidget(min_avg_volt_mv_label,      row++, 0);
    gridLayout->addWidget(ripple_volt_mv_label,         row++, 0);


    row = 3;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,    row++, 1);
    gridLayout->addWidget(max_avg_volt_mv_edit,     row++, 1);
    gridLayout->addWidget(min_avg_volt_mv_edit,      row++, 1);
    gridLayout->addWidget(ripple_volt_mv_edit,         row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);

}
void config_dialog::set_dialog_TC_CAN(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);

    QLabel *timeout_ms_label   = new QLabel("Timeout:", this);


    QLineEdit *timeout_ms_edit     = new QLineEdit(this);

    timeout_ms_edit->setObjectName("timeout_ms");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);

    int row = 3;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    row = 3;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
}
void config_dialog::set_dialog_TC_DUT_1(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);
    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);
    QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);

    QLineEdit *timeout_ms_edit    = new QLineEdit(this);
    QLineEdit *dut_tc_id_edit     = new QLineEdit( this);

    timeout_ms_edit->setValidator(new QIntValidator(0, 999999,timeout_ms_edit ));
    dut_tc_id_edit->setValidator(new QIntValidator(0, 999999, dut_tc_id_edit));

    timeout_ms_edit->setObjectName("timeout_ms");
    dut_tc_id_edit->setObjectName("dut_tc_id");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = this->row_continue;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(dut_tc_id_label,      row++, 0);

    row = this->row_continue;

    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,      row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();
}
void config_dialog::set_dialog_TC_BMS_OTP(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_BMS_CELL_VOLT(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_BMS_GATE_DRIVER(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_TC_BMS_SHUTDOWN(void){
    this->dialog_clear();

}
void config_dialog::set_dialog_CM_IO1(void){
    this->dialog_clear();

}

QString config_dialog::get_dialog_TC_DUT_IO1(void){
    TC_Dut_Io1_Para tc_jig;

    tc_jig.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id")->text().toUInt() ;
    tc_jig.correct_level = this->findChild<QLineEdit *>("correct_level")->text().toUInt() ;
    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.type = TC_DUT_IO1_ID;
    int size = sizeof (TC_Dut_Io1_Para);
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}
/*------------------------------------------------------------------*/
/*------------------------Get Paramaters TestCase-------------------*/
/*------------------------------------------------------------------*/


QString config_dialog::get_dialog_TC_JIG_VOLT1(void){
    TC_Dut_Volt1_Para tc_jig;

    tc_jig.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id")->text().toUInt() ;
    tc_jig.max_avg_volt_mv = this->findChild<QLineEdit *>("max_avg_volt_mv")->text().toUInt() ;
    tc_jig.min_avg_volt_mv = this->findChild<QLineEdit *>("min_avg_volt_mv")->text().toUInt() ;
    tc_jig.ripple_volt_mv = this->findChild<QLineEdit *>("ripple_volt_mv")->text().toUInt() ;
    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.type = TC_JIG_VOLT1_ID;
    int size = sizeof (TC_Dut_Volt1_Para);
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}

QString config_dialog::get_dialog_TC_DUT_IO2(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_DUT_IO3(void){

    TC_Dut_Io3_Para tc_jig;

    tc_jig.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id")->text().toUInt() ;
    tc_jig.io_output_x_channel = this->findChild<QLineEdit *>("io_output_x_channel")->text().toUInt() ;
    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.type = TC_DUT_IO3_ID;
    int size = sizeof (TC_Dut_Io3_Para);
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}
QString config_dialog::get_dialog_TC_JIG_IO1(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_JIG_IO2(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_JIG_IO3(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_JIG_IO4(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_JIG_IO5(void){
    TC_Jig_Io5_Para tc_jig;
    int size = sizeof (TC_Jig_Io5_Para);

    tc_jig.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id")->text().toUInt() ;
    tc_jig.io_input_y_channel = this->findChild<QLineEdit *>("io_input_y_channel")->text().toUInt() ;
    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.type = TC_JIG_IO5_ID;
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}
QString config_dialog::get_dialog_TC_JIG_IO6(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_JIG_IO7(void){
    TC_Jig_Io7_Para tc_jig;
    int size = sizeof (TC_Jig_Io7_Para);

    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.io_output_x_channel = this->findChild<QLineEdit *>("io_output_x_channel")->text().toUInt() ;
    tc_jig.io_output_y_channel = this->findChild<QLineEdit *>("io_output_y_channel")->text().toUInt() ;
    tc_jig.io_input_z_channel = this->findChild<QLineEdit *>("io_input_z_channel")->text().toUInt() ;
    tc_jig.io_output_x_lv = this->findChild<QLineEdit *>("io_output_x_lv")->text().toUInt() ;
    tc_jig.type = TC_JIG_IO7_ID;
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}
QString config_dialog::get_dialog_TC_JIG_VOLT2(void){
    TC_Jig_Volt2_Para tc_jig;

    tc_jig.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id")->text().toUInt() ;
    tc_jig.adc_channel = this->findChild<QLineEdit *>("adc_channel")->text().toUInt() ;
    tc_jig.voltage_devision_ratio_1000 = this->findChild<QLineEdit *>
            ("voltage_devision_ratio_1000")->text().toUInt() ;
    tc_jig.cycle_time_ms = this->findChild<QLineEdit *>("cycle_time_ms")->text().toUInt() ;
    tc_jig.sample_number = this->findChild<QLineEdit *>("sample_number")->text().toUInt() ;
    tc_jig.max_avg_volt_mv = this->findChild<QLineEdit *>("max_avg_volt_mv")->text().toUInt() ;
    tc_jig.min_avg_volt_mv = this->findChild<QLineEdit *>("min_avg_volt_mv")->text().toUInt() ;
    tc_jig.ripple_volt_mv = this->findChild<QLineEdit *>("ripple_volt_mv")->text().toUInt() ;
    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.type = TC_DUT_VOLT1_ID;
    int size = sizeof (TC_Jig_Volt2_Para);
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}
QString config_dialog::get_dialog_TC_JIG_VOLT3(void){

    return nullptr;
}
QString config_dialog::get_dialog_TC_DUT_VOLT1(void){
    TC_Dut_Volt1_Para tc_jig;

    tc_jig.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id")->text().toUInt() ;
    tc_jig.max_avg_volt_mv = this->findChild<QLineEdit *>("max_avg_volt_mv")->text().toUInt() ;
    tc_jig.min_avg_volt_mv = this->findChild<QLineEdit *>("min_avg_volt_mv")->text().toUInt() ;
    tc_jig.ripple_volt_mv = this->findChild<QLineEdit *>("ripple_volt_mv")->text().toUInt() ;
    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.type = TC_DUT_VOLT1_ID;
    int size = sizeof (TC_Dut_Volt1_Para);
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}
QString config_dialog::get_dialog_TC_CAN(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_DUT_1(void){
    TC_Dut1_Para tc_jig;

    tc_jig.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id")->text().toUInt() ;
    tc_jig.timeout_ms = this->findChild<QLineEdit *>("timeout_ms")->text().toUInt() ;
    tc_jig.type = TC_DUT_1_ID;
    int size = sizeof (TC_Dut1_Para);
    uint8_t data[size];
    memcpy(data,(uint8_t*)&tc_jig,size);
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));
    return dataStr;
}
QString config_dialog::get_dialog_TC_BMS_OTP(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_BMS_CELL_VOLT(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_BMS_GATE_DRIVER(void){
    return nullptr;
}
QString config_dialog::get_dialog_TC_BMS_SHUTDOWN(void){
    return nullptr;
}
QString config_dialog::get_dialog_CM_IO1(void){
    return nullptr;
}
/*------------------------------------------------------------------*/
/*------------------------Get Paramaters TestCase-------------------*/
/*------------------------------------------------------------------*/
QString config_dialog::get_par_tc(QString text){
    QString dataStr = nullptr;

    if(text ==  "TC_JIG_VOLT1"){
        dataStr = this->get_dialog_TC_JIG_VOLT1();
    }
    else if(text ==  "TC_DUT_IO1"){
        dataStr = this->get_dialog_TC_DUT_IO1();
    }
    else if(text ==  "TC_DUT_IO2"){
        dataStr = this->get_dialog_TC_DUT_IO2();
    }
    else if( text == "TC_DUT_IO3"){
        dataStr = this->get_dialog_TC_DUT_IO3();
    }
    else if(text == "TC_JIG_IO1"){
        dataStr = this->get_dialog_TC_JIG_IO1();
    }
    else if(text ==  "TC_JIG_IO2"){
        dataStr = this->get_dialog_TC_JIG_IO2();
    }
    else if(text ==  "TC_JIG_IO3"){
        dataStr = this->get_dialog_TC_JIG_IO3();
    }
    else if( text == "TC_JIG_IO4"){
        dataStr = this->get_dialog_TC_JIG_IO4();
    }
    else if(text ==  "TC_JIG_IO5"){
        dataStr = this->get_dialog_TC_JIG_IO5();
    }
    else if(text == "TC_JIG_IO6"){
        dataStr = this->get_dialog_TC_JIG_IO6();
    }
    else if(text ==  "TC_JIG_IO7"){
        dataStr = this->get_dialog_TC_JIG_IO7();
    }
    else if(text == "TC_JIG_VOLT1"){
        dataStr = this->get_dialog_TC_JIG_VOLT1();
    }
    else if(text ==  "TC_JIG_VOLT2"){
        dataStr = this->get_dialog_TC_JIG_VOLT2();
    }
    else if(text ==  "TC_JIG_VOLT3"){
        dataStr = this->get_dialog_TC_JIG_VOLT3();
    }
    else if(text ==  "TC_DUT_VOLT1"){
        dataStr = this->get_dialog_TC_DUT_VOLT1();
    }
    else if(text ==  "TC_CAN"){
        dataStr = this->get_dialog_TC_CAN();
    }
    else if(text ==  "TC_DUT_1"){
        dataStr = this->get_dialog_TC_DUT_1();
    }
    else if(text ==  "TC_BMS_OTP"){
        dataStr = this->get_dialog_TC_BMS_OTP();
    }
    else if(text ==  "TC_BMS_CELL_VOLT"){
        dataStr = this->get_dialog_TC_BMS_CELL_VOLT();
    }
    else if(text ==   "TC_BMS_GATE_DRIVER"){
        dataStr = this->get_dialog_TC_BMS_GATE_DRIVER();
    }
    else if( text == "TC_BMS_SHUTDOWN"){
        dataStr = this->get_dialog_TC_BMS_SHUTDOWN();
    }
    else if(text ==  "CM_IO1"){
        dataStr = this->get_dialog_CM_IO1();
    }
    return dataStr;
}
/*------------------------------------------------------------------*/
/*------------------------Show Paramaters TestCase------------------*/
/*------------------------------------------------------------------*/
void config_dialog::set_dialog_tc(QString text){
    if(text ==  "TC_JIG_VOLT1"){
        this->set_dialog_TC_JIG_VOLT1();
    }
    else if(text ==  "TC_DUT_IO1"){
        this->set_dialog_TC_DUT_IO1();
    }
    else if(text ==  "TC_DUT_IO2"){
        this->set_dialog_TC_DUT_IO2();
    }
    else if( text == "TC_DUT_IO3"){
        this->set_dialog_TC_DUT_IO3();
    }
    else if(text == "TC_JIG_IO1"){
        this->set_dialog_TC_JIG_IO1();
    }
    else if(text ==  "TC_JIG_IO2"){
        this->set_dialog_TC_JIG_IO2();
    }
    else if(text ==  "TC_JIG_IO3"){
        this->set_dialog_TC_JIG_IO3();
    }
    else if( text == "TC_JIG_IO4"){
        this->set_dialog_TC_JIG_IO4();
    }
    else if(text ==  "TC_JIG_IO5"){
        this->set_dialog_TC_JIG_IO5();
    }
    else if(text == "TC_JIG_IO6"){
        this->set_dialog_TC_JIG_IO6();
    }
    else if(text ==  "TC_JIG_IO7"){
        this->set_dialog_TC_JIG_IO7();
    }
    else if(text == "TC_JIG_VOLT1"){
        this->set_dialog_TC_JIG_VOLT1();
    }
    else if(text ==  "TC_JIG_VOLT2"){
        this->set_dialog_TC_JIG_VOLT2();
    }
    else if(text ==  "TC_JIG_VOLT3"){
        this->set_dialog_TC_JIG_VOLT3();
    }
    else if(text ==  "TC_DUT_VOLT1"){
        this->set_dialog_TC_DUT_VOLT1();
    }
    else if(text ==  "TC_CAN"){
        this->set_dialog_TC_CAN();
    }
    else if(text ==  "TC_DUT_1"){
        this->set_dialog_TC_DUT_1();
    }
    else if(text ==  "TC_BMS_OTP"){
        this->set_dialog_TC_BMS_OTP();
    }
    else if(text ==  "TC_BMS_CELL_VOLT"){
        this->set_dialog_TC_BMS_CELL_VOLT();
    }
    else if(text ==   "TC_BMS_GATE_DRIVER"){
        this->set_dialog_TC_BMS_GATE_DRIVER();
    }
    else if( text == "TC_BMS_SHUTDOWN"){
        this->set_dialog_TC_BMS_SHUTDOWN();
    }
    else if(text ==  "CM_IO1"){
        this->set_dialog_CM_IO1();
    }
}
