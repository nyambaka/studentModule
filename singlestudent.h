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

class singleStudent : public QObject
{
    Q_OBJECT
private:
    QMap<QString,QProcess *>processes;
    QJsonObject data;
    QJsonObject result;
    int counter;
    bool suspendQuit;
    void startProcess(QString processName,QString arguments);
    void initialize();
    void endProcess(QString processName);


public:
    explicit singleStudent(QObject *parent = nullptr);
    explicit singleStudent(const QJsonObject &studentData,const QJsonObject &result);
    QString DebugSingleStudent();
    static bool validate(QString value,QString expression);
    void createSqlTable();
    QString mysqlSave();
    QString mysqlSelect(QStringList values,QJsonObject fields);
    bool connectToMysqlDatabase();
    void mysqlSelectQuery(QString query,QJsonObject advancedSearch);


signals:
    void studentNameChanged(const QString newStudentName);
    void studentAdmissionNumberChanged(const QString newStudentAdmission);
    void quit();
    void processStarted();
    void processEnded();
    void startclassprocess();
    void readProcessReady(QString processName);

public slots:
    void readProcess(QString processName);
    void decreaseCounter();
     void sendOutput();
    void increaseCounter();
};

#endif // SINGLESTUDENT_H
