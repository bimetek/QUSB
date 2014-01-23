#include "io_p.h"
#include "clibusb"

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
