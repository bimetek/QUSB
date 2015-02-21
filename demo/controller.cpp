#include "controller.h"
#include <QDebug>
#include <QIODevice>
#include "device.h"


Controller::Controller(QObject *parent) :
    QObject(parent), count(0)
{
    QList<QUSB::Device> devices = QUSB::Device::availableDevices();
    foreach (const QUSB::Device &device, devices)
    {
        qDebug() << "Got device at:" << device.bus() << ":" << device.address();
        qDebug() << "Device info:"<< "Product ID" << device.productId();

        handle = QUSB::Handle::fromVendorIdProductId(
                    device.vendorId(), device.productId());
        qDebug() << "            " << "Product description" <<
                    handle->stringDescriptor(device.product());
        qDebug() << "            " << "Manufacturer" <<
                    handle->stringDescriptor(device.manufacturer());
    }
    handle = QUSB::Handle::fromVendorIdProductId(0xeb1a, 0x299f);
    handle->setParent(this);
    handle->claimInterface(0);
    io = new QUSB::BulkIO(handle, 3, this);
    io->open(QIODevice::ReadOnly);
    connect(
        io, SIGNAL(bytesReceived(QByteArray)),
        this, SLOT(processBytes(QByteArray))
    );
}

Controller::~Controller()
{
    io->close();
}

void Controller::processBytes(const QByteArray &bytes)
{
    QDebug dbg = qDebug();
    for (int i = 0; i < bytes.length(); i++)
        dbg << static_cast<int>(bytes[i]);
    count++;
    if (count >= 4)
        this->deleteLater();
}
