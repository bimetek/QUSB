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
