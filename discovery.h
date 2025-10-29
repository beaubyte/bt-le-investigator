#ifndef DISCOVERY_H
#define DISCOVERY_H

#include <QObject>

class Discovery : public QObject
{
    Q_OBJECT
public:
    explicit Discovery(QObject *parent = nullptr);

signals:

};

#endif // DISCOVERY_H
