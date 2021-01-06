#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>

class QCommandLineParser;
class QCommandLineOption;
class QJsonArray;


class utility : public QObject
{
    Q_OBJECT
public:
    explicit utility(QObject *parent = nullptr);
    QCommandLineOption createShortCommandLineOption(const QJsonArray & val);
    QCommandLineOption createLongCommandlineOption(const QJsonArray & val);
    QCommandLineOption createCommandLineOption(const QJsonArray & val);

signals:

public slots:
};

#endif // UTILITY_H
