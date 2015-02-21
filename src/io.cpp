#include "io.h"
#include "io_p.h"
#include "clibusb"
#include <QtCore/QThread>

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
