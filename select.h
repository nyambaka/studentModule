#ifndef SELECT_H
#define SELECT_H

#include <QObject>
class QJsonObject;
class QString;

class select : public QObject
{
    Q_OBJECT
private:
    QString query;

public:
    explicit select(QObject *parent = nullptr);
    explicit select(QString query="");
    QJsonObject result(bool isMain=false);
signals:

public slots:
};

#endif // SELECT_H
