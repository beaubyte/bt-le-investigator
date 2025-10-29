#include <QCoreApplication>
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include "discovery.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    qInfo() << "Initializing the application";
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;

    QList<QBluetoothAddress> remotes;
    // please connect to me to the local bluetooth device :3
    if (localDevice.isValid()) {
        qInfo() << "Powering on Bluetooth";
        localDevice.powerOn();
        localDeviceName = localDevice.name();
        qInfo() << "Using interface " << localDeviceName;
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        remotes = localDevice.connectedDevices();
    } else {
        qWarning() << "Failed to connect to Bluetooth";
    }
    qInfo() << "Number of connected devices: " << remotes.length();
    for (int i = 0; i < remotes.length(); i++){
        qInfo() << "Found: " << remotes[i].toString();
    }
    Discovery *discovery = new Discovery();
    discovery->startDeviceDiscovery();

    return a.exec();
}


