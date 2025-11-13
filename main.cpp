#include <QCoreApplication>
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>
#include "discovery.h"
#include "macdatabase.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Initializing the application";
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    QTextStream stream(stdin);
    QString host;
    qInfo() << "Where is the device being deployed?";
    host = stream.readLine();
    qInfo() << "Connecting to the database server";
    macdatabase db;
    bool ok = db.connectDatabase();
    if (ok) {
        qInfo() << "Connected to database successfully!";
        qDebug() << "Looking for:";
        QString queryText = "select macaddress, friendlyname from bluetooth.findable";
        QSqlQuery query = db.dbquery(queryText);
        if (query.first() == true){
            while (query.next()) {
                QString macaddress = query.value(0).toString();
                QString name = query.value(1).toString();
                qDebug() << macaddress << name;
            }
        } else {
            qWarning() << "!! Query returned no results";
        }
    } else {
        qWarning() << "!! Failed to connect to database";
    }

    // --------------------- reads local bluetooth as test ---------------------
    QList<QBluetoothAddress> remotes;
    // please connect to me to the local bluetooth device :3
    if (localDevice.isValid()) {
        qDebug() << "Powering on Bluetooth";
        localDevice.powerOn();
        localDeviceName = localDevice.name();
        qInfo() << "Using interface " << localDeviceName;
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
        remotes = localDevice.connectedDevices();
    } else {
        qWarning() << "Failed to connect to Bluetooth";
    }
    qInfo() << "Actively connected devices: " << remotes.length();
    for (int i = 0; i < remotes.length(); i++){
        qDebug() << "Found: " << remotes[i].toString();
    }
    // -------------------------------------------------------------------------

    Discovery *discovery = new Discovery();
    // discovery takes in the database you wish to store the found devices as a pointer
    discovery->startDeviceDiscovery(&db, host);

    return a.exec();
}


