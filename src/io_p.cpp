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
#include "io.h"
#include "io_p.h"

namespace QUSB
{

IOPrivate::IOPrivate(IO *q, Handle *handle, int endpoint) :
    q_ptr(q), handle(handle), endpoint(endpoint), readTransfer(0),
    readThread(0), readChannel(0)
{
}

IOPrivate::~IOPrivate()
{
    if (this->readTransfer && this->readTransfer->buffer)
        delete [] this->readTransfer->buffer;
}

void IOPrivate::transferCallback(libusb_transfer *transfer)
{
    if (!transfer || !transfer->user_data)
        return;
    IOPrivate *obj = reinterpret_cast<IOPrivate *>(transfer->user_data);
    if (transfer == obj->readTransfer)
    {
        switch (transfer->status)
        {
        case LIBUSB_TRANSFER_CANCELLED:
            // Transfers are cancelled when they close. Do cleanup for it.
            // See also: IO::close()
            libusb_free_transfer(transfer);
            break;
        case LIBUSB_TRANSFER_COMPLETED:
            emit obj->q_ptr->bytesReceived(QByteArray(
                reinterpret_cast<char *>(transfer->buffer),
                transfer->actual_length
            ));
            if (!obj->submit(transfer))     // Continue reading
                obj->readTransfer = 0;
            break;
        default:
            // TODO: Implement the rest of the API
            break;
        }
    }
}

libusb_transfer *IOPrivate::alloc()
{
    return libusb_alloc_transfer(0);
}

void IOPrivate::fill(libusb_transfer *, int, uchar *, int)
{
}

bool IOPrivate::submit(libusb_transfer *transfer)
{
    int r = libusb_submit_transfer(transfer);   // Continue reading.
    if (r)
    {
        if (transfer && transfer->buffer)
            delete [] transfer->buffer;
        libusb_free_transfer(transfer);
    }
    return (r == 0);
}

}   // namespace QUSB
