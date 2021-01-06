#include "utility.h"
#include<QCommandLineOption>
#include<QCommandLineParser>
#include<QJsonArray>
#include<QDebug>

utility::utility(QObject *parent) : QObject(parent)
{

}


QCommandLineOption utility::createCommandLineOption(const QJsonArray &val){

    return val[0].toBool()?createShortCommandLineOption(val):createLongCommandlineOption(val);
}

QCommandLineOption utility::createShortCommandLineOption(const QJsonArray &val){

     return QCommandLineOption(val[4].toString(),val[5].toString(),val[6].toString(),val[7].toString());
}

QCommandLineOption utility::createLongCommandlineOption(const QJsonArray &val){
     return QCommandLineOption(val[4].toString(),val[5].toString(),val[6].toString(),val[7].toString());
}

