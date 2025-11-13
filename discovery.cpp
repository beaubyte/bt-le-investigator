#include "discovery.h"
Discovery::Discovery(QObject *parent)
    : QObject{parent}
{}
// step 1: look for nearby devices
void Discovery::startDeviceDiscovery(macdatabase* btdb, QString hostname){
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(30000); // this is just for testing
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(addDeviceDiscovered(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(concludeScan()));
    connect(discoveryAgent, SIGNAL(cancelled()), this, SLOT(concludeScan()));
    db = btdb;
    hostLocation = hostname;
    qInfo() << "Collecting nearby devices, please wait...";
    discoveryAgent->start();
}

// step 2: check if the devices are tiles, if they are: add them
void Discovery::addDeviceDiscovered(const QBluetoothDeviceInfo &device){
    qDebug() << "Found device " << device.name() << " at address " << device.address().toString();
    /*
    if (device.address().toString() == "CB:DC:B2:35:34:4D" || device.address().toString() == "E9:2B:38:87:b0:73" || device.address().toString() == "E2:F2:F9:C7:B9:76" || device.address().toString() == "80:E1:26:77:C8:11"){
        qInfo() << "Tracked Tile found!!";
    }
    */
    deviceList.appendDevice(device);
    // this needs to be where nearby devices are sent back somehow to a function
}
void Discovery::concludeScan(){
    qInfo() << "Scan has ended";
    deviceList.listCapturedMACs();
    QString newEvent;
    newEvent.append("insert into bluetooth.device_events (macaddress, name, time, location) values ");
    QVector<QVector<QString>> devices = getDevices();
    for (int i = 0; i < devices.length(); i++) {
        newEvent.append("('");
        newEvent.append(devices[i][0]);
        newEvent.append("', '");
        newEvent.append(devices[i][1]);
        newEvent.append("', '");
        newEvent.append(devices[i][2]);
        newEvent.append("', '");
        newEvent.append(hostLocation);
        if (i < devices.length()-1){
            newEvent.append("'), ");
        } else {
            newEvent.append("');");
        }
    }
    qInfo() << newEvent;
    QSqlQuery eventQuery;
    if (eventQuery.exec(newEvent)){
        qInfo() << "Inserted devices into database";
    } else {
        qWarning() << "Failed to insert data: " << eventQuery.lastError();
    }
    QCoreApplication:exit(0);
}

QList<QList<QString>> Discovery::getDevices(){
    QDateTime now = QDateTime::currentDateTime();
    QList<QBluetoothDeviceInfo> list = deviceList.getList();
    QList<QList<QString>> btInfo(list.length());
    qInfo() << list.length();
    for (int i = 0; i < list.length(); i++){
        btInfo[i].append(list[i].address().toString());
        btInfo[i].append(list[i].name());
        btInfo[i].append(now.currentDateTime().toString(Qt::ISODate));
        qInfo() << list[i].address().toString();
    }
    return btInfo;
}
