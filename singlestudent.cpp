#include "singlestudent.h"
#include<iostream>
#include<QFile>
#include<QSettings>

singleStudent::singleStudent(QObject *parent) : QObject(parent)
{

}

singleStudent::singleStudent(const QJsonObject &studentData):data(studentData){

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
    return data["admission"].toString() + data["name"].toString();
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
