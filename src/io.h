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

#ifndef QUSB_IO_H
#define QUSB_IO_H

#include <QtCore/QIODevice>
#include "global.h"

namespace QUSB
{

class Handle;
class IOPrivate;

class QUSB_SHARED_EXPORT IO : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IO)

protected:
    IOPrivate *d_ptr;
    IO(IOPrivate *d, QObject *parent = 0);

public:
    explicit IO(Handle *handle, int endpoint, QObject *parent = 0);
    virtual ~IO();

    virtual bool open(QIODevice::OpenMode openMode);
    virtual void close();

signals:
    void bytesReceived(QByteArray bytes);
};

}   // namespace QUSB

#endif // QUSB_IO_H
