#ifndef SDT_H
#define SDT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SDT; }
QT_END_NAMESPACE

class SDT : public QMainWindow
{
    Q_OBJECT

public:
    SDT(QWidget *parent = nullptr);
    ~SDT();
public slots:

private:
    Ui::SDT *ui;
};
#endif // SDT_H
