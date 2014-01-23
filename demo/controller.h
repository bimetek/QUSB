#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "handle.h"
#include "bulkio.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);
    virtual ~Controller();

public slots:
    void processBytes(const QByteArray &bytes);

private:
    QUSB::Handle *handle;
    QUSB::BulkIO *io;
};

#endif // CONTROLLER_H
