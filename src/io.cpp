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
#include "io.h"
#include "io_p.h"

namespace QUSB
{

IO::IO(Handle *handle, int endpoint, QObject *parent) :
    QObject(parent), d_ptr(new IOPrivate(this, handle, endpoint))
{
}

IO::IO(IOPrivate *d, QObject *parent) :
    QObject(parent), d_ptr(d)
{

}

IO::~IO()
{
    delete d_ptr;
}

bool IO::open(QIODevice::OpenMode openMode)
{
    Q_D(IO);
    Q_UNUSED(openMode);

    // TODO: Implement open mode. This is a read-only implementation.
    d->readTransfer = d->alloc();
    d->fill(d->readTransfer, LIBUSB_ENDPOINT_IN, new uchar[1024], 1024);
    bool ok = d->submit(d->readTransfer);
    if (!ok)
    {
        d->readTransfer = 0;
        return false;
    }

    return true;
}

void IO::close()
{
    Q_D(IO);
    if (!d->readTransfer)
        return;

    if (!d->readTransfer->dev_handle)
    {
        // Nothing to transfer. We can clean up now safely.
        libusb_free_transfer(d->readTransfer);
        return;
    }

    // Needs to cancel the transfer first. Cleanup happens in the
    // callback. (IOPrivate::transferCallback)
    libusb_cancel_transfer(d->readTransfer);
}

}   // namespace QUSB
