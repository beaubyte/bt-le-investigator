#include <QCoreApplication>
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>
#include <QSettings>
#include "discovery.h"
#include "macdatabase.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Initializing the application";
    QSettings settings("bt-investigator","beaubyte");
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    QTextStream stream(stdin);
    QString host;

    qInfo() << "Where is the device being deployed?";
    host = stream.readLine();

    // ------------------ configuration for the database -------------------------------
    if (settings.contains("db/host")){
        qInfo() << "Do you want to reset database settings? (y/n)";
        QString resetValues = stream.readLine();
        if (resetValues.contains("y")){
            settings.remove("db/host");
            qDebug() << "Reset host value";
            settings.remove("db/name");
            qDebug() << "Reset name value";
            settings.remove("db/username");
        }
    }

    qInfo() << "Connecting to the database server";
    macdatabase db;
    if (!(settings.contains("db/host"))){
        qInfo() << "What is the hostname of the database?";
        settings.setValue("db/host",stream.readLine());
    }
    if (!(settings.contains("db/name"))){
        qInfo() << "What is the name of your database?";
        settings.setValue("db/name",stream.readLine());
    }
    if (!(settings.contains("db/username"))){
        qInfo() << "What is the username to access the database?";
        settings.setValue("db/username",stream.readLine());
    }
    qInfo() << "What is the password to access the database?";
    QString password = stream.readLine();

    bool ok = db.connectDatabase(&settings, password);
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

    // --------------------- reads local bluetooth for debug purposes ---------------------
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


