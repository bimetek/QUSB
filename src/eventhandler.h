#ifndef QUSB_EVENTHANDLER_H
#define QUSB_EVENTHANDLER_H

#include <QtCore/QObject>
struct libusb_context;
class QThread;

namespace QUSB
{

#include <QObject>

class EventHandler : public QObject
{
    Q_OBJECT

public:
    EventHandler(libusb_context *context, QObject *parent = 0);

    int timer;
    libusb_context *context;

public slots:
    void handle();

protected:
    virtual void timerEvent(QTimerEvent *);

private:

};

class Destroyer : public QObject
{
    Q_OBJECT
    QThread *thread;
    EventHandler *handler;

public:
    Destroyer(QThread *thread, EventHandler *handler, QObject *parent = 0);

    ~Destroyer();
};

}   // namespace QUSB

#endif // QUSB_EVENTHANDLER_H
