#include "devicebox.h"

devicebox::devicebox(QObject *parent)
    : QObject{parent}
{}

void devicebox::appendDevice(QBluetoothDeviceInfo q){
    targetDeviceList.append(q);
}

void devicebox::listCapturedMACs(){
    qInfo() << "Devices of note captured: ";
    for (int i = 0; i < targetDeviceList.length(); i++){
        qInfo() << targetDeviceList[i].name() << " - " << targetDeviceList[i].address().toString();
    }
}
