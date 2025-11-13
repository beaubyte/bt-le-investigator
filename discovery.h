#ifndef DISCOVERY_H
#define DISCOVERY_H
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QObject>
#include <QSqlError>
#include "devicebox.h"
#include "macdatabase.h"

class Discovery : public QObject
{
    Q_OBJECT
public:
    explicit Discovery(QObject *parent = nullptr);
    void startDeviceDiscovery(macdatabase*);

public slots:
    void addDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void concludeScan();
    QList<QList<QString>> getDevices();
signals:

private:
    devicebox deviceList;
    macdatabase* db;
};

#endif // DISCOVERY_H
