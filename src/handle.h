#ifndef QUSB_HANDLE_H
#define QUSB_HANDLE_H

#include "device.h"

namespace QUSB
{

class HandlePrivate;

class SHARED_EXPORT Handle
{
    Q_DECLARE_PRIVATE(Handle)
    HandlePrivate *d_ptr;

    Handle(libusb_device_handle *rawhandle);

public:
    Handle(const Device &device);
    ~Handle();

    int claimInterface(int num);
    int releaseInterface(int num);

    libusb_device_handle *rawhandle() const;

    static Handle *fromVendorIdProductId(quint16 vid, quint16 pid);
};

}   // namespace QUSB

#endif // QUSB_HANDLE_H
