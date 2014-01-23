#include "controller.h"
#include <QDebug>
#include <QIODevice>
#include "device.h"


Controller::Controller(QObject *parent) :
    QObject(parent)
{
    QList<QUSB::Device *> devices = QUSB::Device::availableDevices();
    foreach (QUSB::Device *device, devices)
        qDebug() << device->address();
    handle = QUSB::Handle::fromVendorIdProductId(0xeb1a, 0x299f);
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
    delete handle;
}

void Controller::processBytes(const QByteArray &bytes)
{
    QDebug dbg = qDebug();
    for (int i = 0; i < bytes.length(); i++)
        dbg << static_cast<int>(bytes[i]);
}
