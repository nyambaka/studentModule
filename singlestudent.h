#ifndef SINGLESTUDENT_H
#define SINGLESTUDENT_H

#include <QObject>
#include<QString>
#include<QJsonObject>
#include<stdinlistner.h>
#include<QDebug>

class singleStudent : public QObject
{
    Q_OBJECT
private:
    QJsonObject data;
    stdInListner * listener;

public:
    explicit singleStudent(QObject *parent = nullptr);
    explicit singleStudent(const QJsonObject &studentData);
    QString DebugSingleStudent();

signals:
    void studentNameChanged(const QString newStudentName);
    void studentAdmissionNumberChanged(const QString newStudentAdmission);

public slots:
    void  setStudentName(const QString newStudentName);
    void  setStudentAdmissionNumber(const QString newStudentAdmission);
    void  runCommand(const QString command);
    void  receiveWork(const QString sampleCommand);
    std::string sendOutput(std::string sampleOutput);
};

#endif // SINGLESTUDENT_H
