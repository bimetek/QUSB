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

#include "clibusb"
#include "bulkio.h"
#include "handle.h"
#include "io_p.h"

namespace QUSB
{

class BulkIOPrivate : public IOPrivate
{
    Q_DECLARE_PUBLIC(BulkIO)

public:
    BulkIOPrivate(IO *q, Handle *handle, int endpoint) :
        IOPrivate(q, handle, endpoint) {}

    virtual void fill(libusb_transfer *tran, int flag, uchar *buf, int len)
    {
        libusb_fill_bulk_transfer(
            tran,
            this->handle->rawhandle(),
            flag | this->endpoint,
            buf,
            len,
            IOPrivate::transferCallback,
            this,
            0
        );
    }
};

BulkIO::BulkIO(BulkIOPrivate *d, QObject *parent) :
    IO(d, parent)
{
}

BulkIO::BulkIO(Handle *handle, int endpoint, QObject *parent) :
    IO(new BulkIOPrivate(this, handle, endpoint), parent)
{
}

}   // namespace QUSB
