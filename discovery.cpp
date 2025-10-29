#include "discovery.h"
Discovery::Discovery(QObject *parent)
    : QObject{parent}
{}

void Discovery::startDeviceDiscovery(){
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(addDeviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(addDeviceDiscovered(QBluetoothDeviceInfo)));
    // im gonna start this discovery so hard
    discoveryAgent->start();
}

void Discovery::addDeviceDiscovered(const QBluetoothDeviceInfo &device){
    qInfo() << "Found device " << device.name() << " at address " << device.address().toString();
}
