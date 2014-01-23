#include "device.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QMutex>
#include <QtCore/QThread>
#include "clibusb"
#include "eventhandler.h"

namespace QUSB
{

// ============================================================== DevicePrivate

class DevicePrivate
{
    Q_DECLARE_PUBLIC(Device)
    Device *q_ptr;

public:
    DevicePrivate(Device *q, libusb_device *rawdevice) :
        q_ptr(q), rawdevice(rawdevice) {}

    libusb_device *rawdevice;
};



// ===================================================================== Device

Device::Device(libusb_device *rd) :
    d_ptr(new DevicePrivate(this, rd))
{
    libusb_ref_device(rd);
}

libusb_device *Device::rawdevice() const
{
    return d_ptr->rawdevice;
}

libusb_context *Device::rawcontext()
{
    static QMutex mutex;
    static libusb_context *context = 0;
    static EventHandler *handler = 0;
    static Destroyer *destroyer = 0;
    if (!context)
    {
        mutex.lock();
        if (!context)
        {
            int r = libusb_init(&context);
#ifdef QT_DEBUG
            libusb_set_debug(context, 3);
#endif
            if (r)
                qWarning("Failed to initiaize LibUSB");
            if (context)
            {
                handler = new EventHandler(context);
                QThread *thread = new QThread();
                handler->moveToThread(thread);
                thread->start();

                destroyer = new Destroyer(thread, handler);
                QObject::connect(
                    qApp, SIGNAL(aboutToQuit()),
                    destroyer, SLOT(deleteLater())
                );
            }
        }
        mutex.unlock();
    }
    return context;
}

Device::Device(const Device &d) :
    d_ptr(new DevicePrivate(this, d.rawdevice()))
{
    libusb_ref_device(d.rawdevice());
}

Device::~Device()
{
    libusb_unref_device(d_ptr->rawdevice);
    delete d_ptr;
}

quint8 Device::bus() const
{
    return libusb_get_bus_number(d_ptr->rawdevice);
}

quint8 Device::address() const
{
    return libusb_get_device_address(d_ptr->rawdevice);
}

Device::Speed Device::speed() const
{
    int rsp = libusb_get_device_speed(d_ptr->rawdevice);
    Speed sp = SpeedUnknown;
    switch (rsp)
    {
    case LIBUSB_SPEED_LOW:
        sp = SpeedLow;
        break;
    case LIBUSB_SPEED_FULL:
        sp = SpeedLow;
        break;
    case LIBUSB_SPEED_HIGH:
        sp = SpeedLow;
        break;
    case LIBUSB_SPEED_SUPER:
        sp = SpeedLow;
        break;
    default:
        break;
    }
    return sp;
}

Device &Device::operator=(const Device &)
{
    return *this;
}

QList<Device *> Device::availableDevices()
{
    libusb_context *context = Device::rawcontext();
    libusb_device **deviceArray = 0;

    ssize_t deviceCount = libusb_get_device_list(context, &deviceArray);
    QList<Device *> devices;
    for (ssize_t i = 0; i < deviceCount; i++)
        devices.append(new Device(deviceArray[i]));
    libusb_free_device_list(
        deviceArray,
        1   // Deref the device instances because DevicePrivate holds it.
    );

    return devices;
}

}   // namespace QUSB
