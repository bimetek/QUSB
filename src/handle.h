#ifndef QUSB_HANDLE_H
#define QUSB_HANDLE_H

#include <QtCore/QObject>
#include "device.h"
struct libusb_device_handle;

namespace QUSB
{

class HandlePrivate;

class SHARED_EXPORT Handle : public QObject
{
    Q_DECLARE_PRIVATE(Handle)
    HandlePrivate *d_ptr;

    Q_DISABLE_COPY(Handle)
    Handle(
        const Device &device, libusb_device_handle *rawhandle,
        QObject *parent = 0
    );

public:
    explicit Handle(const Device &device, QObject *parent = 0);
    ~Handle();

    int claimInterface(int num);
    int releaseInterface(int num);

    libusb_device_handle *rawhandle() const;

    static Handle *fromVendorIdProductId(quint16 vid, quint16 pid);
};

}   // namespace QUSB

#endif // QUSB_HANDLE_H
