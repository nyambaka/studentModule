#include "singlestudent.h"
#include<iostream>
#include<QFile>
#include<QSettings>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<QStringList>

singleStudent::singleStudent(QObject *parent) : QObject(parent)
{
    initialize();
}

singleStudent::singleStudent(const QJsonObject &studentData,const QJsonObject &result):data(studentData),result(result){
    initialize();
}

QString singleStudent::DebugSingleStudent(){
    return data["age"].toString() + data["firstName"].toString();
}

bool singleStudent::validate(QString data, QString regularExpr){
    QRegularExpression rx(regularExpr);
    QRegularExpressionMatch match= rx.match(data);
    return match.hasMatch();
}

void singleStudent::sendOutput(){
    QJsonDocument doc= QJsonDocument(result);
    std::cout<<doc.toJson(QJsonDocument::JsonFormat::Compact).toStdString();
}

void singleStudent::createSqlTable(){
    //    Qstring sqlQuery="";
    //    if(!result.contains("error")){
    //       sqlQuery+="create table "
    //    }
}

QString singleStudent::mysqlSelect(QStringList values,QJsonObject fields){
    if(data.length()==0)
        return "";
    QString query="";
    query+="select ";
    bool first =true;
    QStringList limitAndOffestKey,fieldValueKey;
    fieldValueKey= data.keys();
    limitAndOffestKey<<"limit"<<"offset";
    int length=values.length();
    if(length>0)
    {
        query+="`";
        query+=values.join("`,`");
        query+="`";
    }
    else
        query+="*";
    query+=" from student ";
    if(data.length()==0){
        query+="where 1 limit 10";
    }else{
        foreach (QString val, fieldValueKey) {
            if(first){
                query+="where ";
                first=false;
            }else{
                query+=" and ";
            }
            if(limitAndOffestKey.contains(val))
                continue;
            query+=val+" ";
            query +=fields.value(val).toArray()[9].toString();
            query+=" '";
            query +=fields.value(val).toArray()[10].toString();
            query +=data.value(val).toString();
            query +=fields.value(val).toArray()[10].toString();
            query+="'";
        }
        foreach (QString lastVal, limitAndOffestKey) {
            if(!data.value(lastVal).isUndefined())
            {
                query +=" "+lastVal+"=";
                query +=data.value(lastVal).toString();
                query +=" ";
            }
        }
    }
    return query;
}


QString singleStudent::mysqlSave(){
    if(data.length()>0){
        QStringList field = data.keys();
        QStringList subject;
        subject<<"subject"<<"id"<<"name";
        QStringList definateValue,unencryptedValue,normalField,unencryptedfield;

        foreach (QString tempDefinateValue, field) {
            if(subject.contains(tempDefinateValue)){
                unencryptedValue.append(data.value(tempDefinateValue).toString().trimmed());
                unencryptedfield.append(tempDefinateValue);
            }else{
                definateValue.append(data.value(tempDefinateValue).toString().trimmed());
                normalField.append(tempDefinateValue);
            }
        }

        if(normalField.length()>0 || unencryptedValue.length()>0){
            QString returnValue="";
            returnValue += "INSERT INTO `student` (`";
            returnValue += (normalField+unencryptedfield).join("`, `");
            returnValue += "`) VALUES (";
            returnValue += definateValue.length()>0?"MD5('":"";
            returnValue += definateValue.join("'), MD5('");
            returnValue += definateValue.length()>0?"')":"";
            returnValue += definateValue.length()>0 && unencryptedValue.length()>0?",":"";
            returnValue += unencryptedValue.length()>0?"'":"";
            returnValue += unencryptedValue.join("', '");
            returnValue += definateValue.length()>0 && unencryptedValue.length()>0?"')":definateValue.length()>0?")":unencryptedValue.length()>0?"`)":"";
            return returnValue;
        }else{
            return "";
        }
        return "";
    }else{
        return "";
    }
}

bool singleStudent::connectToMysqlDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("school");
    db.setUserName("root");
    db.setPassword("");
    return db.open();
}


void singleStudent::mysqlSelectQuery(QString query,QJsonObject advancedSearch){
    select * selector= new select(query);
    result = selector->result(true);
    if(advancedSearch.count()>0){
        suspendQuit= true;
//        QString studentId= result.value("id").toString();
//        if(studentId.isEmpty()){
//            return mainResult;
//        }
        QJsonObject::iterator it = advancedSearch.begin();
        while (it!=advancedSearch.end()) {
            startProcess(it.key(),it.value().toString());
            it++;
        }
    }
    else{
        emit processEnded();
    }
}


void singleStudent::startProcess(QString processName,QString arguments){
    processes.insert(processName,new QProcess(this));
    connect(processes.value(processName),QProcess::readyReadStandardOutput,this,[this,processName](){
        emit readProcessReady(processName);
    });
    processes.value(processName)->start(processName+" "+arguments,QIODevice::ReadWrite);
    emit processStarted();
}


void singleStudent::endProcess(QString processName){
    if(processName.contains(processName)){
        processes[processName]->close();
        emit processEnded();
    }
}

void singleStudent::decreaseCounter(){
    if(counter!=0){
        counter=counter-1;
    }
    if(counter==0){
        sendOutput();
        emit quit();
    }
    emit quit();
}

void singleStudent::initialize(){
    suspendQuit=false;
    counter=0;
    connect(this,singleStudent::processStarted,this,singleStudent::increaseCounter);
    connect(this,singleStudent::processEnded,this,singleStudent::decreaseCounter);
    connect(this,singleStudent::readProcessReady,this,singleStudent::readProcess);
    processes=QMap<QString ,QProcess *>();
}

void singleStudent::readProcess(QString processName){
    QString resultString(processes[processName]->readAllStandardOutput());
    result.insert(processName,resultString);
    emit endProcess(processName);
}

void singleStudent::increaseCounter(){
    counter =counter+1;
}
