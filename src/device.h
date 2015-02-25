/******************************************************************************
**
** Copyright (C) 2014 BIMEtek Co. Ltd.
**
** This file is part of QUSB.
**
** QUSB is free software: you can redistribute it and/or modify it under the
** terms of the GNU Lesser General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** QUSB is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
** details.
**
** You should have received a copy of the GNU General Public License along with
** this file. If not, see <http://www.gnu.org/licenses/>.
**
******************************************************************************/

#ifndef QUSB_DEVICE_H
#define QUSB_DEVICE_H

#include <QtCore/QList>
#include <QtCore/QObject>
#include "global.h"
struct libusb_context;
struct libusb_device;

namespace QUSB
{

class Handle;
class DevicePrivate;

void setDebugLevel(int level);

class QUSB_SHARED_EXPORT Device : public QObject
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
    int maximumPacketSize(uchar endpoint) const;
    int maximumIsoPacketSize(uchar endpoint) const;
    qint32 vendorId() const;        // A quint16, or -1
    qint32 productId() const;       // A quint16, or -1
    qint16 product() const;         // A quint8, or -1
    qint16 manufacturer() const;    // A quint8, or -1
    qint16 serialNumber() const;    // A quint8, or -1
    qint16 deviceClass() const;
    qint16 deviceSubClass() const;

    Device &operator=(const Device &d);

    static QList<Device> availableDevices();
};

}   // namespace QUSB

#endif // QUSB_DEVICE_H
