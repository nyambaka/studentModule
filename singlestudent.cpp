#include "singlestudent.h"

singleStudent::singleStudent(QObject *parent) : QObject(parent)
{

//    listener->connect(stdInLister,receivedCommand,this,runCommand);

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

    qDebug()<<"received a command";
}
