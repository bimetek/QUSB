#include <QtCore/QThread>
#include "clibusb"
#include "eventhandler.h"

namespace QUSB
{

EventHandler::EventHandler(libusb_context *context, QObject *parent) :
    QObject(parent), timer(0), context(context)
{
    timer = startTimer(1);
}

void EventHandler::handle()
{
    libusb_handle_events_completed(this->context, 0);
}

void EventHandler::timerEvent(QTimerEvent *)
{
    QMetaObject::invokeMethod(this, "handle");
}

Destroyer::Destroyer(QThread *thread, EventHandler *handler, QObject *parent) :
    QObject(parent), thread(thread), handler(handler) {}

Destroyer::~Destroyer()
{
    handler->killTimer(handler->timer);
    handler->deleteLater();
    thread->quit();
    thread->deleteLater();
    libusb_exit(handler->context);
}

}   // namespace QUSB
