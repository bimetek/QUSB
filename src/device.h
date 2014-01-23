#ifndef QUSB_DEVICE_H
#define QUSB_DEVICE_H

#include "global.h"
#include <QtCore/QList>
struct libusb_context;
struct libusb_device;

namespace QUSB
{

class DevicePrivate;

class SHARED_EXPORT Device
{
    Q_DECLARE_PRIVATE(Device)
    DevicePrivate *d_ptr;

    explicit Device(libusb_device *rawdevice);
    Device &operator=(const Device &d);     // Disabled

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

    Device(const Device &d);
    ~Device();

    quint8 bus() const;
    quint8 address() const;
    Speed speed() const;

    static QList<Device *> availableDevices();
};

}   // namespace QUSB

#endif // QUSB_DEVICE_H
