#include "select.h"
#include<QJsonObject>
#include<QString>
#include<QSqlRecord>
#include<QVariant>
#include<QSqlQuery>

select::select(QObject *parent) : QObject(parent)
{
    query="";
}

select::select(QString inputQuery){
    query=inputQuery;
}

QJsonObject select::result(bool isMain){
    QSqlQuery q;
    QJsonObject resObject={};
    if (query.isEmpty()){
        resObject["error"]="empty query";
        return resObject;
    }
    if(q.exec(query)){
        while (q.next()) {
            QJsonObject record={};
            QSqlRecord rec = q.record();
            int length=rec.count();
            for(int i=0;i<length;i++){
                QVariant field =rec.fieldName(i);
                QVariant value = rec.value(i);
                record[field.toString()]=value.toString();
            }
            if(isMain){
                resObject[record.value("id").toString()]=record;
            }else{
                resObject = record;
            }
        }
    }else{
        resObject["error"]="error in executing sql query";
        resObject["sql"]= query;
    }
    return resObject;
}
