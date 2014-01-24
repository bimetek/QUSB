#ifndef QUSB_BULKIO_H
#define QUSB_BULKIO_H

#include "io.h"

namespace QUSB
{

class BulkIOPrivate;

class QUSB_SHARED_EXPORT BulkIO : public IO
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BulkIO)

protected:
    BulkIO(BulkIOPrivate *d, QObject *parent = 0);

public:
    BulkIO(Handle *handle, int endpoint, QObject *parent = 0);
};

}   // namespace QUSB

#endif // QUSB_BULKIO_H
