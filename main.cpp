#include <QCoreApplication>
#include<QApplication>
#include<QMessageBox>
#include"singlestudent.h"
#include<QJsonObject>
#include<QDebug>
#include<QJsonValue>
#include<QCommandLineParser>
#include<QCommandLineOption>
#include<QStringList>
#include<iostream>
#include<QProcess>

#include<iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("student");

    QJsonObject studentObject{

    };

//    QCommandLineParser parser;

//    parser.setApplicationDescription("single student handler");

//    //command line options ....name ..description...valueName...default value
//    QCommandLineOption admission= QCommandLineOption("admission","Name","admission","unkwon");
//    QCommandLineOption name= QCommandLineOption("name","admission number","name","00");
//    QCommandLineOption amode= QCommandLineOption(QStringList()<<"o"<<"output","verbose mode","a","34");
//    QCommandLineOption amode2= QCommandLineOption(QStringList()<<"u"<<"aOut","verbose mode","u","34");
//    QCommandLineOption texrCommand=QCommandLineOption("nkjdkf");
//    texrCommand.setDefaultValue("jdkf");


//    //add all option on the command line
//    parser.addOptions({admission,name,amode,texrCommand,amode2});

//    //add help and and process the application

//   parser.addHelpOption();
//   parser.process(a);

    QCommandLineParser parser;
    parser.setApplicationDescription("used to edit a subjet ");
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsCompactedShortOptions);

    QCommandLineOption name= QCommandLineOption("name","name","unkwon","00");
    QCommandLineOption code = QCommandLineOption("code","code","unkwon","00");

    QCommandLineOption p = QCommandLineOption("p");
    p.setDefaultValue("kim");

    QCommandLineOption o = QCommandLineOption("o");
    o.setDefaultValue("house");

  singleStudent * sampleStudent= new singleStudent();
    parser.addOptions({name,code,p,o});

    parser.process(a);
    if(parser.isSet(o)){

    }
    sampleStudent->runCommand("h");
    return a.exec();
}
