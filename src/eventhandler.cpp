/******************************************************************************
**
** Copyright (C) 2014 BIMEtek Co. Ltd.
**
** This file is part of QUSB.
**
** QUSB is free software: you can redistribute it and/or modify it under the
** terms of the GNU Lesser General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** QUSB is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
** details.
**
** You should have received a copy of the GNU General Public License along with
** this file. If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

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
