#ifndef QUSB_IO_H
#define QUSB_IO_H

#include <QtCore/QIODevice>
#include "global.h"

namespace QUSB
{

class Handle;
class IOPrivate;

class QUSB_SHARED_EXPORT IO : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IO)

protected:
    IOPrivate *d_ptr;
    IO(IOPrivate *d, QObject *parent = 0);

public:
    explicit IO(Handle *handle, int endpoint, QObject *parent = 0);
    virtual ~IO();

    virtual bool open(QIODevice::OpenMode openMode);
    virtual void close();

signals:
    void bytesReceived(QByteArray bytes);
};

}   // namespace QUSB

#endif // QUSB_IO_H
