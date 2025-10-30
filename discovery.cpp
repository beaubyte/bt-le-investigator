#include "discovery.h"
Discovery::Discovery(QObject *parent)
    : QObject{parent}
{}

// step 1: look for nearby devices
void Discovery::startDeviceDiscovery(){
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(10000); // this is just for testing
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(addDeviceDiscovered(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(concludeScan()));
    connect(discoveryAgent, SIGNAL(cancelled()), this, SLOT(concludeScan()));

    // im gonna start this discovery so hard
    discoveryAgent->start();
}

// step 2: check if the devices are tiles, if they are: add them
void Discovery::addDeviceDiscovered(const QBluetoothDeviceInfo &device){
    qInfo() << "Found device " << device.name() << " at address " << device.address().toString();
    if (device.address().toString() == "CB:DC:B2:35:34:4D" || device.address().toString() == "E9:2B:38:87:b0:73" || device.address().toString() == "E2:F2:F9:C7:B9:76"){
        qInfo() << "Tracked Tile found!!";
        deviceList.appendDevice(device);
    }
    // this needs to be where nearby devices are sent back somehow to a function
}
void Discovery::concludeScan(){
    qInfo() << "Scan has ended";
    deviceList.listCapturedMACs();
}
