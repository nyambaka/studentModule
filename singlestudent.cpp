#include "singlestudent.h"
#include<iostream>
#include<QFile>
#include<QSettings>
#include<QRegularExpression>
#include<QRegularExpressionMatch>

singleStudent::singleStudent(QObject *parent) : QObject(parent)
{

}

singleStudent::singleStudent(const QJsonObject &studentData,const QJsonObject &result):data(studentData),result(result){

}

void singleStudent::setStudentAdmissionNumber(const QString newStudentAdmission){
   data["admission"]=newStudentAdmission;
   emit studentAdmissionNumberChanged(newStudentAdmission);
}

void singleStudent::setStudentName(const QString newStudentName){
    data["name"] = newStudentName;
    emit studentNameChanged(newStudentName);
}

QString singleStudent::DebugSingleStudent(){
    return data["age"].toString() + data["firstName"].toString();
}

bool singleStudent::validate(QString data, QString regularExpr){
   QRegularExpression rx(regularExpr);
   QRegularExpressionMatch match= rx.match(data);
   return match.hasMatch();
}

void singleStudent::runCommand(const QString ){
    std::cout<<"o has been called";
}

void singleStudent::receiveWork(const QString work ){
    std::cout<<"sample output"+work.toUpper().toStdString();
}

std::string singleStudent::sendOutput(std::string sampleOutput){
    return sampleOutput;
}
