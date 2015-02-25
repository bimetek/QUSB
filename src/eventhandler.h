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

#ifndef QUSB_EVENTHANDLER_H
#define QUSB_EVENTHANDLER_H

#include <QtCore/QObject>
struct libusb_context;
class QThread;

namespace QUSB
{

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
