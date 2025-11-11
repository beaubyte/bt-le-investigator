#ifndef MACDATABASE_H
#define MACDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class macdatabase : public QObject
{
    Q_OBJECT
public:
    explicit macdatabase(QObject *parent = nullptr);
    bool connectDatabase();
    QSqlQuery dbquery(QString);
private:
    QSqlDatabase db;
signals:
};

#endif // MACDATABASE_H
