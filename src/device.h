#ifndef QUSB_DEVICE_H
#define QUSB_DEVICE_H

#include "global.h"
#include "clibusb"
#include <QtCore/QList>

namespace QUSB
{

class DevicePrivate;

class SHARED_EXPORT Device
{
    Q_DECLARE_PRIVATE(Device)
    DevicePrivate *d_ptr;

    Device(libusb_device *rawdevice);

    libusb_device *rawdevice() const;
    static libusb_context *rawcontext();

public:

    enum Speed
    {
        SpeedUnknown = LIBUSB_SPEED_UNKNOWN,
        SpeedLow = LIBUSB_SPEED_LOW,
        SpeedFull = LIBUSB_SPEED_FULL,
        SpeedHigh = LIBUSB_SPEED_HIGH,
        SpeedSuper = LIBUSB_SPEED_SUPER
    };

    friend class Handle;

    ~Device();

    quint8 bus() const;
    quint8 address() const;
    Speed speed() const;

    static QList<Device *> availableDevices();
};

}   // namespace QUSB

#endif // QUSB_DEVICE_H
