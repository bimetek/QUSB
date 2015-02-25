# QUSB

Qt wrapper classes for LibUSB 1.0.

This project contains a library that wraps LibUSB functionalities into Qt classes to ease usage in Qt applications.


## WARNING: WORK IN PROGRESS

This is very much a work in progress. No support whatsoever. Use at your own risks. I only implemented the interface I need. If you feel you can improve this project please feel free to do anything you want with the code. The API and implementation may change drastically if there are good ideas, without any compatibility (both API- and binary-wise) in mind. Be careful if you want to upgrade the version of QUSB for an existing project.


## License

QUSB is released under GNU Lesser General Public License, version 3 or later. A copy of the license should have been included in the project source code distribution.

Please also note that since QUSB depends on LibUSB, you will likely need to consider the availibility of LibUSB when you re-distribute the binary and/or source of it when you use QUSB. LibUSB is licensed under the ​GNU Lesser General Public License version 2.1 or later. See the [project home of LibUSB](http://www.libusb.org) for more detailed information.


## Building from source

### Dependencies

* Qt (tested on 4.8)
* LibUSB 1.0

### Building

Use the standard build process of Qt projects, e.g. on Linux and OS X with GNU Make:

    qmake
    make

Pass `CONFIG+=demo` if you want to build the demo project with the library:

    qmake CONFIG+=demo
    make

### Installing

On Linux and OS X with GNU Make:

    make install

By default, the library binary and headers will be installed under `/usr/local`, which my require administrative priviledges. To override this, set `QUSB_INSTALL_PREFIX` when you run qmake:

    qmake QUSB_INSTALL_PREFIX=$HOME/usr
    make
    make install


## Usages

Everything is under the `QUSB` namespace. Subsequent code snippets will omit the namespace when referring to QUSB classes.

The main interface is the `Device` class. You can use the static function `Device::availableDevices()` to get a list of available USB devices on your machine. Member functions exist for you to query information of the device; read the USB specification and documentation of USB to understand what they mean.

To interact with a device, you need to create a `Handle` class. This creates a handle to a USB device. With a handle, you can then open a communication for an endpoint on the device you’re handling via subclasses of the `IO` class. Currently only bulk IO is implemented, via the `BuikIO` class. The `BuikIO` class works similarly to Qt’s `QIODevice`.[1] You can use it to open a communication, read/write data to and from it, and close it when you’re done.

The communication between the USB host and client are done asynchronously. LibUSB hosts its a run loop, and use C function callbacks to handle the transmission. QUSB automatically creates and maintains a LibUSB context for you, and integrate the callbacks to Qt’s event loop system, so Qt’s standard signal-slot mechanism should be all you need. It doesn’t hurt if you know how things work behind the scenes, though.

There is also a global (inside the `QUSB` namespace, that is) function `setDebugLevel` that can be used to set the information verbosity of LibUSB. See documentation of LibUSB for a list of appropriate log level values.


[1]: The IO classes are not really subclasses of `QIODevice`, just *work similarly*. This may change in the future; helps are welcomed.
