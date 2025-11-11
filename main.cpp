#include <QCoreApplication>
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "discovery.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "Initializing the application";
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    qInfo() << "Connecting to the database server";
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("prism.panda-mirach.ts.net");
    db.setDatabaseName("investigator");
    db.setUserName("testuser");
    db.setPassword("TheDayWeMet"); // production version will use offuscated password

    bool ok = db.open();
    if (ok) {
        qInfo() << "Connected to database successfully!";
        QSqlQuery query("select macaddress, friendlyname from bluetooth.findable");
        if (query.first() == true){
            while (query.next()) {
                QString macaddress = query.value(0).toString();
                QString name = query.value(1).toString();
                qInfo() << macaddress << name;
            }
        } else {
            qWarning() << "!! Query returned no results";
        }
    } else {
        qWarning() << "!! Failed to connect to database";
    }


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


