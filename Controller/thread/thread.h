#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include "QTimer"
#include <QThread>

class thread : public QObject
{
    Q_OBJECT
private:
    QTimer *timer_10ms;
    QTimer *timer_1ms;
    QTimer *timer_testing_process;
    QTimer *timer_Notification;

public:
    explicit thread(QObject *parent = nullptr);
    static thread *start_timer();
public slots:
    void timeout_timer_1ms_handle();
    void timeout_timer_10ms_handle();
    void timeout_timer_testing_process_handle();
    void timeout_timer_Notification_handle();

signals:

};

class get_event : public QThread
{
public:
    get_event();
protected:
    void run();
};


#endif // THREAD_H
