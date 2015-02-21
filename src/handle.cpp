#include "clibusb"
#include "device.h"
#include "handle.h"

namespace QUSB
{

class HandlePrivate
{
    Q_DECLARE_PUBLIC(Handle)
    Handle *q_ptr;

public:
    HandlePrivate(
            Handle *q, const Device &device, libusb_device_handle *rawhandle);
    virtual ~HandlePrivate();

    libusb_device_handle *rawhandle;
    Device device;
    QList<int> claimedInterfaces;
};

HandlePrivate::HandlePrivate(
        Handle *q, const Device &device, libusb_device_handle *rawhandle) :
    q_ptr(q), rawhandle(rawhandle), device(device) {}

HandlePrivate::~HandlePrivate()
{
    foreach (int num, claimedInterfaces)
        libusb_release_interface(rawhandle, num);
    libusb_close(rawhandle);
}


Handle::Handle(const Device &device, libusb_device_handle *rawhandle,
        QObject *parent) :
    QObject(parent), d_ptr(new HandlePrivate(this, device, rawhandle))
{
}

libusb_device_handle *Handle::rawhandle() const
{
    return d_func()->rawhandle;
}

Handle::Handle(const Device &device, QObject *parent) :
    QObject(parent), d_ptr(new HandlePrivate(this, device, 0))
{
    Q_D(Handle);
    int r = libusb_open(device.rawdevice(), &d->rawhandle);
    if (r)
        qWarning("Unable to obtain device handle.");

}

Handle::~Handle()
{
    delete d_ptr;
}

int Handle::activeConfiguration() const
{
    int rc = 0;
    int config = 0;
    //This method returns a returncode and puts the data you actually
    //want in an int you pass by reference.
    rc = libusb_get_configuration(d_ptr->rawhandle,&config);
    switch(rc)
    {
    case 0:
        if(config != 0)
            return config;
        else
        {
            qWarning("The device is in an unconfigured state");
            return 0;
        }
    case LIBUSB_ERROR_NO_DEVICE:
        qWarning("The device has been disconnected");
        break;
    default:
        qWarning("An error has occured");
        break;
    }
    return rc;
}

int Handle::setConfiguration(int config) const
{
    int rc = 0;
    rc = libusb_set_configuration(d_ptr->rawhandle, config);
    switch(rc)
    {
    case 0://success
        return 0;
    case LIBUSB_ERROR_NO_DEVICE:
        qWarning("The device has been disconnected");
        break;
    case LIBUSB_ERROR_BUSY:
        qWarning("The interface is already claimed");
        break;
    case LIBUSB_ERROR_NOT_FOUND:
        qWarning("The requested configuration does not exist");
        break;
    default:
        qWarning("An error has occured");
        break;
    }
    return rc;
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
    Q_D(Handle);
    int r = libusb_release_interface(d->rawhandle, num);
    if (r)
        qWarning("Failed to release interface %d", num);
    else
        d->claimedInterfaces.removeOne(num);
    return r;
}

int Handle::setInterfaceAlternateSetting(int interfaceNumber, int alternateSetting) const
{
    int rc = libusb_set_interface_alt_setting(d_ptr->rawhandle, interfaceNumber, alternateSetting);
    switch(rc)
    {
    case 0://success
        return 0;
    case LIBUSB_ERROR_NOT_FOUND:
        qWarning("The interface is not claimed or the requested alternate setting does not exist");
        break;
    case LIBUSB_ERROR_NO_DEVICE:
        qWarning("The device has been disconnected");
        break;
    default:
        qWarning("An error has occured");
    }
    return rc;
}

Handle *Handle::fromVendorIdProductId(quint16 vid, quint16 pid)
{
    libusb_device_handle *rawhandle = libusb_open_device_with_vid_pid(
        Device::rawcontext(), vid, pid
    );
    if (!rawhandle)
        return 0;
    libusb_device *rawdevice = libusb_get_device(rawhandle);
    Device device(rawdevice);
    return new Handle(device, rawhandle);
}

QString Handle::stringDescriptor(quint32 index) const
{
    const int bufferSize = 256;
    char buffer[bufferSize];
    int r = libusb_get_string_descriptor_ascii(
                rawhandle(), index, reinterpret_cast<uchar *>(buffer),
                bufferSize);
    if (r < 0)  // TODO: Need to do something with the error code.
        qWarning("Error getting description");
    return QString::fromAscii(buffer, bufferSize);
}

}   // namespace QUSB
