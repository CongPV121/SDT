#ifndef MC_H
#define MC_H

#include <QMainWindow>

namespace Ui {
class mc;
}

class mc : public QMainWindow
{
    Q_OBJECT

public:
    explicit mc(QWidget *parent = nullptr);
    ~mc();

private:
    Ui::mc *ui;
};

#endif // MC_H
