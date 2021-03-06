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

singleStudent::singleStudent(const QJsonObject &studentData):data(studentData){
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
    QJsonDocument doc= QJsonDocument(*result);
    std::cout<<doc.toJson(QJsonDocument::JsonFormat::Compact).toStdString();
}

void singleStudent::output(QJsonObject output){
    QJsonDocument doc= QJsonDocument(output);
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
        values.append("id");
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

void singleStudent::mysqlSelectQuery(QStringList values,QJsonObject fields,QJsonObject advancedSearch){
    QString query = mysqlSelect(values,fields);
    select * selector= new select(query);
    selector->resultMap(advancedSearch);
    output(selector->response());
}

void singleStudent::initialize(){
    suspendQuit=false;
    result=new QJsonObject();
}
