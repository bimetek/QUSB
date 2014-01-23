#include "handle.h"
#include "clibusb"

namespace QUSB
{

class HandlePrivate
{
    Q_DECLARE_PUBLIC(Handle)
    Handle *q_ptr;

public:
    HandlePrivate(Handle *q) :
        q_ptr(q), rawhandle(0) {}

    libusb_device_handle *rawhandle;
    QList<int> claimedInterfaces;
};

Handle::Handle(libusb_device_handle *rawhandle) :
    d_ptr(new HandlePrivate(this))
{
    d_ptr->rawhandle = rawhandle;
}

libusb_device_handle *Handle::rawhandle() const
{
    return d_ptr->rawhandle;
}

Handle::Handle(const Device &device) :
    d_ptr(new HandlePrivate(this))
{
    int r = libusb_open(device.rawdevice(), &d_ptr->rawhandle);
    if (r)
        qWarning("Unable to obtain device handle.");
}

Handle::Handle(const Handle &)
{
}

Handle &Handle::operator=(const Handle &h)
{
    return h;
}

Handle::~Handle()
{
    foreach (int num, d_ptr->claimedInterfaces)
        libusb_release_interface(d_ptr->rawhandle, num);
    libusb_close(d_ptr->rawhandle);
    delete d_ptr;
}

int Handle::claimInterface(int num)
{
    int r = libusb_claim_interface(d_ptr->rawhandle, num);
    if (r)
        qWarning("Failed to claim interface %d", num);
    else
        d_ptr->claimedInterfaces.append(num);
    return r;
}

int Handle::releaseInterface(int num)
{
    int r = libusb_release_interface(d_ptr->rawhandle, num);
    if (r)
        qWarning("Failed to release interface %d", num);
    else
        d_ptr->claimedInterfaces.removeOne(num);
    return r;
}

Handle *Handle::fromVendorIdProductId(quint16 vid, quint16 pid)
{
    libusb_device_handle *rawhandle = libusb_open_device_with_vid_pid(
        Device::rawcontext(), vid, pid
    );
    return new Handle(rawhandle);
}

}   // namespace QUSB
