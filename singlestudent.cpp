#include "singlestudent.h"
#include<iostream>
#include<QFile>

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
    listener = new  stdInListner(this);
    listener->start();
    connect(listener, &stdInListner::receivedCommand, this, &singleStudent::receiveWork);
}

void singleStudent::receiveWork(const QString work ){
    std::cout<<"sample output"+work.toStdString();
}

std::string singleStudent::sendOutput(std::string sampleOutput){
    return sampleOutput;
}
