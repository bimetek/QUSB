#ifndef QUSB_IO_P_H
#define QUSB_IO_P_H

#include "io.h"
struct libusb_transfer;
class QThread;

namespace QUSB
{

class Channel;

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
