#include "io.h"
#include "io_p.h"
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
    libusb_cancel_transfer(d_ptr->readTransfer);
    // Transfer cleanup happens in the callback.
}

}   // namespace QUSB
