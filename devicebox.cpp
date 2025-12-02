#include "devicebox.h"

devicebox::devicebox(QObject *parent)
    : QObject{parent}
{}

// adds a new device to the box
void devicebox::appendDevice(QBluetoothDeviceInfo q){
    targetDeviceList.append(q);
}

// lists the captured MAC addresses of the devices in the scan to the terminal for debug purposes
void devicebox::listCapturedMACs(){
    QDateTime now = QDateTime::currentDateTime();
    qInfo() << "Devices of note captured: ";
    for (int i = 0; i < targetDeviceList.length(); i++){
        qInfo() << targetDeviceList[i].name() << " - " << targetDeviceList[i].address().toString() << " - " << now;
    }
}

QList<QBluetoothDeviceInfo> devicebox::getList(){
    return targetDeviceList;
}
