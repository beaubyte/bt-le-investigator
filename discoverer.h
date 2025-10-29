#ifndef DISCOVERER_H
#define DISCOVERER_H

#include <QObject>
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
class Discoverer : public QObject
{
    Q_OBJECT
public:
    explicit Discoverer(QObject *parent = nullptr);

signals:
public slots:
    void addDeviceDiscovered(const QBluetoothDeviceInfo &info);
};

#endif // DISCOVERER_H
