#include <QDebug>
#include <QIODevice>
#include "controller.h"
#include "device.h"


Controller::Controller(QObject *parent) :
    QObject(parent), handle(0), io(0), count(0)
{
    QList<QUSB::Device> devices = QUSB::Device::availableDevices();
    foreach (const QUSB::Device &device, devices)
    {
        qDebug() << "Got device at:" << device.bus() << ":" << device.address();
        qDebug() << "Device info:";
        qDebug() << "\tProduct ID" << device.productId();

        handle = QUSB::Handle::fromVendorIdProductId(
                    device.vendorId(), device.productId());
        qDebug() << "\tProduct description" <<
                    handle->stringDescriptor(device.product());
        qDebug() << "\tManufacturer" <<
                    handle->stringDescriptor(device.manufacturer());
    }

    // Modify these to suit your needs.
    quint16 vendor = 0xeb1a;
    quint16 product = 0x299f;

    handle = QUSB::Handle::fromVendorIdProductId(vendor, product);
    if (handle)
    {
        handle->setParent(this);
        handle->claimInterface(0);
        io = new QUSB::BulkIO(handle, 3, this);
    }
    else
    {
        qDebug() << QString("Could not open device with ID: 0x%1, 0x%2")
                    .arg(vendor, 4, 16, QChar('0'))
                    .arg(product, 4, 16, QChar('0'));
    }

    if (io)
    {
        io->open(QIODevice::ReadOnly);
        connect(io, SIGNAL(bytesReceived(QByteArray)),
                this, SLOT(processBytes(QByteArray)));
    }
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
