#ifndef SINGLESTUDENT_H
#define SINGLESTUDENT_H

#include <QObject>
#include<QString>
#include<QJsonObject>
#include<QDebug>
#include<QRegExp>

class singleStudent : public QObject
{
    Q_OBJECT
private:
    QJsonObject data;
    QJsonObject result;

public:
    explicit singleStudent(QObject *parent = nullptr);
    explicit singleStudent(const QJsonObject &studentData,const QJsonObject &result);
    QString DebugSingleStudent();
    static bool validate(QString value,QString expression);
    void createSqlTable();

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
