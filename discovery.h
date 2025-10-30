#ifndef DISCOVERY_H
#define DISCOVERY_H
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QObject>
#include "devicebox.h"

class Discovery : public QObject
{
    Q_OBJECT
public:
    explicit Discovery(QObject *parent = nullptr);
    void startDeviceDiscovery();

public slots:
    void addDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void concludeScan();
signals:

private:
    devicebox deviceList;
};

#endif // DISCOVERY_H
