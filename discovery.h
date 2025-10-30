#ifndef DISCOVERY_H
#define DISCOVERY_H
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QObject>

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

};

#endif // DISCOVERY_H
