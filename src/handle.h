#ifndef QUSB_HANDLE_H
#define QUSB_HANDLE_H

#include "device.h"
struct libusb_device_handle;

namespace QUSB
{

class HandlePrivate;

class SHARED_EXPORT Handle
{
    Q_DECLARE_PRIVATE(Handle)
    HandlePrivate *d_ptr;

    Handle(libusb_device_handle *rawhandle);
    Handle(const Handle &);     // Disabled
    Handle &operator=(const Handle &h);     // Disabled

public:
    explicit Handle(const Device &device);
    ~Handle();

    int claimInterface(int num);
    int releaseInterface(int num);

    libusb_device_handle *rawhandle() const;

    static Handle *fromVendorIdProductId(quint16 vid, quint16 pid);
};

}   // namespace QUSB

#endif // QUSB_HANDLE_H
