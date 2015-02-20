#ifndef QUSB_DEVICE_H
#define QUSB_DEVICE_H

#include "global.h"
#include "clibusb"

#include <QtCore/QList>
struct libusb_context;
struct libusb_device;

namespace QUSB
{
class Handle;
class DevicePrivate;
void setDebugLevel(int level);

class QUSB_SHARED_EXPORT Device
{
    Q_DECLARE_PRIVATE(Device)
    DevicePrivate *d_ptr;

    explicit Device(libusb_device *rawdevice);

    libusb_device *rawdevice() const;
    static libusb_context *rawcontext();

public:

    // This actually matches LibUSB's constants, but we don't want to
    // completely depend on that.
    enum Speed
    {
        SpeedUnknown = 0,
        SpeedLow,
        SpeedFull,
        SpeedHigh,
        SpeedSuper
    };

    friend class Handle;
    friend void setDebugLevel(int level);

    Device(const Device &d);
    ~Device();

    quint8 bus() const;
    quint8 address() const;
    Speed speed() const;
    qint32 vendorId() const;    // A qint16, or -1
    qint32 productId() const;   // A qint16, or -1
    qint32 product() const; //A qint16, or -1
    qint32 manufacturer() const; //A qint16, or -1
    qint32 serialNumber() const; //A qint16, or -1

    static QString getStringDescriptor(QUSB::Handle *dev, quint32 index);
    Device &operator=(const Device &d);

    static QList<Device> availableDevices();
};

}   // namespace QUSB

#endif // QUSB_DEVICE_H
