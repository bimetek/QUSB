#ifndef QUSB_GLOBAL_H
#define QUSB_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(QUSB_LIBRARY)
#  define QUSB_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define QUSB_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QUSB_GLOBAL_H
