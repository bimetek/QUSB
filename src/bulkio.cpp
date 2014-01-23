#include "bulkio.h"
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
