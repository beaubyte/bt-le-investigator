#ifndef DEVICEBOX_H
#define DEVICEBOX_H
#include <QBluetoothPermission>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QObject>
#include <QDateTime>

class devicebox : public QObject
{
    Q_OBJECT
public:
    explicit devicebox(QObject *parent = nullptr);
    void appendDevice(QBluetoothDeviceInfo q);
    void listCapturedMACs();
    QList<QBluetoothDeviceInfo> getList();
signals:

private:
    QList<QBluetoothDeviceInfo> targetDeviceList;
};
#endif // DEVICEBOX_H
