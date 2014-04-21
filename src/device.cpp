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

qint32 Device::vendorId() const
{
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(d_ptr->rawdevice, &desc);
    if (r)
        return -1;
    return desc.idVendor;
}

qint32 Device::productId() const
{
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(d_ptr->rawdevice, &desc);
    if (r)
        return -1;
    return desc.idProduct;
}

Device &Device::operator=(const Device &d)
{
    this->d_ptr->rawdevice = d.d_ptr->rawdevice;
    return *this;
}

QList<Device> Device::availableDevices()
{
    libusb_context *context = Device::rawcontext();
    libusb_device **deviceArray = 0;

    ssize_t deviceCount = libusb_get_device_list(context, &deviceArray);
    QList<Device> devices;
    for (ssize_t i = 0; i < deviceCount; i++)
        devices.append(Device(deviceArray[i]));
    libusb_free_device_list(
        deviceArray,
        1   // Deref the device instances because DevicePrivate holds it.
    );

    return devices;
}

void setDebugLevel(int level)
{
    libusb_set_debug(Device::rawcontext(), level);
}

}   // namespace QUSB
