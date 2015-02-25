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

#ifndef QUSB_HANDLE_H
#define QUSB_HANDLE_H

#include <QtCore/QObject>
#include "global.h"
struct libusb_device_handle;

namespace QUSB
{

class Device;
class HandlePrivate;

class QUSB_SHARED_EXPORT Handle : public QObject
{
    Q_DECLARE_PRIVATE(Handle)
    HandlePrivate *d_ptr;

    Q_DISABLE_COPY(Handle)
    Handle(
        const Device &device, libusb_device_handle *rawhandle,
        QObject *parent = 0
    );

public:
    explicit Handle(const Device &device, QObject *parent = 0);
    ~Handle();

    int activeConfiguration() const;
    int setConfiguration(int config) const;
    int claimInterface(int num);
    int releaseInterface(int num);
    int setInterfaceAlternateSetting(int,int) const;

    libusb_device_handle *rawhandle() const;

    static Handle *fromVendorIdProductId(quint16 vid, quint16 pid);

    QString stringDescriptor(quint32 index) const;
};

}   // namespace QUSB

#endif // QUSB_HANDLE_H
