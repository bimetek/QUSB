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

#ifndef QUSB_IO_P_H
#define QUSB_IO_P_H

#include <QtCore/QtGlobal>
struct libusb_transfer;
class QThread;

namespace QUSB
{

class Channel;
class IO;

class IOPrivate
{
    Q_DECLARE_PUBLIC(IO)

protected:
    IO *q_ptr;

public:
    IOPrivate(IO *q, Handle *handle, int endpoint);
    virtual ~IOPrivate();

    // Things to override.
    virtual libusb_transfer *alloc();
    virtual void fill(libusb_transfer *tran, int flag, uchar *buf, int len);

    bool submit(libusb_transfer *transfer);

    static void transferCallback(libusb_transfer *transfer);

    Handle *handle;
    int endpoint;
    libusb_transfer *readTransfer;
    QByteArray readBuffer;
    QThread *readThread;
    Channel *readChannel;
};

}   // namespace QUSB

#endif // QUSB_IO_P_H
