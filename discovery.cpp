#include "discovery.h"
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
Discovery::Discovery(QObject *parent)
    : QObject{parent}
{
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    // im gonna start this discovery so hard
    discoveryAgent->start();

}
