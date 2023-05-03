#ifndef PRODUCT_TESTING_H
#define PRODUCT_TESTING_H

#include <QDialog>

namespace Ui {
class product_testing;
}

class product_testing : public QDialog
{
    Q_OBJECT

public:
    explicit product_testing(QWidget *parent = nullptr);
    ~product_testing();
    static product_testing* get_product_testing();

private:
    Ui::product_testing *ui;
};

#endif // PRODUCT_TESTING_H
