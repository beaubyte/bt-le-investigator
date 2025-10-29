#ifndef DISCOVERER_H
#define DISCOVERER_H

#include <QObject>

class discoverer : public QObject
{
    Q_OBJECT
public:
    explicit discoverer(QObject *parent = nullptr);

signals:
};

#endif // DISCOVERER_H
