#ifndef SINGLESTUDENT_H
#define SINGLESTUDENT_H

#include <QObject>
#include<QString>
#include<QJsonObject>
#include<QDebug>
#include<QRegExp>
#include<QJsonDocument>
#include<iostream>
#include<QJsonArray>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>
#include<QProcess>
#include"select.h"
#include<QJsonArray>
#include<QMap>
#include<QVariant>

class singleStudent : public QObject
{
    Q_OBJECT
private:
    QMap<QString,QProcess *>processes;
    QMap<QString,QVariant>* interMediateResult;
    QJsonObject data;
    QJsonObject * result;
    bool suspendQuit;
    void startProcess(QString processName,QString arguments,QString identifier);
    void initialize();
    QString mysqlSelect(QStringList values,QJsonObject fields);
    void output(QJsonObject output);

public:
    explicit singleStudent(QObject *parent = nullptr);
    explicit singleStudent(const QJsonObject &studentData);
    QString DebugSingleStudent();
    static bool validate(QString value,QString expression);
    void createSqlTable();
    QString mysqlSave();
    bool connectToMysqlDatabase();
    void mysqlSelectQuery(QStringList values,QJsonObject fields,QJsonObject advancedSearch);

signals:
    void quit();

public slots:
    void sendOutput();

};

#endif // SINGLESTUDENT_H
