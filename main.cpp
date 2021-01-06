#include <QCoreApplication>
#include<QApplication>
#include"singlestudent.h"
#include<QJsonObject>
#include<QDebug>
#include<QJsonValue>
#include<QCommandLineParser>
#include<QCommandLineOption>
#include<QStringList>
#include<iostream>
#include<QJsonDocument>
#include<QFile>
#include<QTextStream>
#include<QJsonValue>
#include<QJsonArray>
#include<utility.h>
#include<QList>
#include<QRegExp>
#include<QValidator>
#include<QRegularExpression>
#include<QRegularExpressionMatch>

#include<iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("student");
    QCoreApplication::setApplicationVersion("1.0.0");


    QJsonObject studentData= QJsonObject();
    QJsonObject result = QJsonObject();

    QFile * studentTemp = new QFile(":/student/se.json");
    if(!studentTemp->open(QFile::ReadOnly)){
        std::cout<<"could not open file for reading and writing";
        return 0;
    }


    utility * tempUtility = new utility();

     QString fileContent(studentTemp->readAll());
     QJsonDocument studentDoc = QJsonDocument::fromJson(fileContent.toUtf8());
     QJsonObject studentObj = studentDoc.object();

    QCommandLineParser parser;
    parser.setApplicationDescription("used to edit a subjet ");
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsCompactedShortOptions);

    QList<QCommandLineOption> pOptions;
    foreach (auto val, studentObj) {
       pOptions<<tempUtility->createCommandLineOption(val.toArray());
    }
    parser.addOptions(pOptions);

    QList<QString>ControlOptions;
    ControlOptions<<"output"<<"interactive"<<"input"<<"create";

    //commandline Options that control the use of the class;

    QCommandLineOption interactive=QCommandLineOption("iteractive","interactive mode","interactive","false");
    QCommandLineOption output =QCommandLineOption("output","output format","output","text");
    QCommandLineOption input=QCommandLineOption("input","Input Source","input","std");
    QCommandLineOption create = QCommandLineOption("create","Create a new Student","create","false");
    QCommandLineOption validate = QCommandLineOption("validate","Validate the input","validate","true");

    parser.addOptions({interactive,output,input,create,validate});
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    QStringList options(parser.optionNames());
    bool hasErrors=false;


    foreach (QString providedOptions, options) {

        if(!singleStudent::validate(parser.value(providedOptions),studentObj[providedOptions].toArray()[1].toString())){
            hasErrors=true;
            result.insert(providedOptions,studentObj[providedOptions].toArray()[8].toString());
//            qDebug()<<studentObj[providedOptions].toArray()[5].toString()<<":error  "<<studentObj[providedOptions].toArray()[8].toString();
        }
        else{
            studentData.insert(providedOptions,parser.value(providedOptions));
        }
    }

    if(!hasErrors){
       singleStudent * tempStudent = new singleStudent(studentData,studentData);


    }else{
        result.insert("error","true");
        QJsonDocument doc= QJsonDocument(result);
        qDebug()<<doc.toJson(QJsonDocument::JsonFormat::Compact);
    }

    a.quit();
    return 0;
}
