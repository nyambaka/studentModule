#ifndef SELECT_H
#define SELECT_H

#include <QObject>
#include<QMap>
#include<QJsonObject>
class QVariant;
#include<QString>
#include<QVariant>
#include<QMap>
#include<QList>

class select : public QObject
{
    Q_OBJECT
private:
    QString query;
    QList<QMap<QString,QVariant>>mainresultlist;
    QMap<QString,QList<QString>>childResult;
    QMap<QString,QVariant>mainResult;
    QJsonObject childQuery(QString query);

public:
    explicit select(QObject *parent = nullptr);
    explicit select(QString query="");
    QJsonObject result(bool isMain=false);
    void resultMap(QJsonObject advancedSearch);
    QJsonObject response();
    QMap<QString,QVariant> childSelect(QString table ="",QString id="");

signals:

public slots:
};

#endif // SELECT_H
