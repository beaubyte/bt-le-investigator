#include <QCoreApplication>
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include "discovery.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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


