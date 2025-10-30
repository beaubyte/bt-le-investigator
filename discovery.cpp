#include "discovery.h"
Discovery::Discovery(QObject *parent)
    : QObject{parent}
{}

// step 1: look for nearby devices
void Discovery::startDeviceDiscovery(){
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(10000); // this is just for testing
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(addDeviceDiscovered(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished(QBluetoothDeviceInfo)), this, SLOT(concludeScan()));
    connect(discoveryAgent, SIGNAL(cancelled(QBluetoothDeviceInfo)), this, SLOT(concludeScan()));

    // im gonna start this discovery so hard
    discoveryAgent->start();
}

// step 2: check if the devices are tiles
void Discovery::addDeviceDiscovered(const QBluetoothDeviceInfo &device){
    qInfo() << "Found device " << device.name() << " at address " << device.address().toString();
    if (device.address().toString() == "CB:DC:B2:35:34:4D"){
        qInfo() << "Tracked Tile found!!";
    }
    // this needs to be where nearby devices are sent back somehow to a function
}
void Discovery::concludeScan(){
    qInfo() << "Scan has ended";
}
