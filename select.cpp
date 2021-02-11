#include "select.h"
#include<QSqlRecord>
#include<QSqlQuery>
#include<QDebug>

select::select(QObject *parent) : QObject(parent)
{
    query="";
}

select::select(QString inputQuery){
    query=inputQuery;
}

void select::resultMap(QJsonObject advancedSearch){
    QSqlQuery q;
    QMap<QString,QVariant>temprecordresult;
    if (query.isEmpty()){
        temprecordresult.insert("error","empty query");
        mainresultlist.append(temprecordresult);
        return;
    }
    if(q.exec(query)){
        while (q.next()) {
            QSqlRecord rec = q.record();
            int length=rec.count();

            for(int i=0;i<length;i++){
                QVariant field =rec.fieldName(i);
                QVariant value = rec.value(i);
                if(field.toString()=="id"){
                   QJsonObject::iterator it= advancedSearch.begin();
                    while(it!= advancedSearch.end()){
                        temprecordresult.insert(it.key(),childSelect(it.key(),value.toString()));
                        it++;
                    }
                }
                temprecordresult[field.toString()]=value.toString();
            }
            mainresultlist.append(temprecordresult);
        }
        return;
    }else{
        temprecordresult.insert("error","error in executing sql query");
        temprecordresult.insert("sql",query);
        mainresultlist.append(temprecordresult);
    }
}

QMap<QString,QVariant> select::childSelect(QString table,QString id){
    QMap<QString,QVariant>values;
    if(table.isEmpty()|| id.isEmpty())
        return values;
    QSqlQuery q;
    QSqlQuery innerQuery;
    QString query="select `"+table+"` from student"+table+" where student="+id;
    if(q.exec(query)){
        while (q.next()) {
            QString inQUery = "select id,name from "+table+" where id="+q.value(0).toString();
            innerQuery.exec(inQUery);
            while(innerQuery.next()){
                values.insert(innerQuery.value(0).toString(),innerQuery.value(1));
            }
        }
    }
    return values;
}

QJsonObject select::childQuery(QString query){
    QJsonObject returnValue;
    if(query.isEmpty())
        return returnValue; ;
    QSqlQuery q;
    if(q.exec(query)){
        while (q.next()) {
            returnValue[q.value(0).toString()]=q.value(1).toString();
        }
    }
    return returnValue;
}

QJsonObject select::response(){
    QMap<QString,QVariant>showingResult;
    foreach (auto ca, mainresultlist) {
        showingResult.insert(ca.value("id").toString(),ca);
    }
    return QJsonObject::fromVariantMap(showingResult);
}
