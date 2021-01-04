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
#include<QResource>
#include<QTextStream>

#include<iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("student");

    QFile * studentTemp = new QFile(":/student/secondary.json");
//    studentTemp->setOpenMode(QFile::openMode(studentTemp->Append));
    if(!studentTemp->open(QFile::ReadOnly)){
        std::cout<<"could not open file for reading and writing";
        return 0;
    }


     QString fileContent(studentTemp->readAll());
     QJsonDocument studentDoc = QJsonDocument::fromJson(fileContent.toUtf8());
     QJsonObject studentObj = studentDoc.object();
     QStringList list;
     list<<"name";
     foreach (QString temp, list) {
         if(studentObj.contains(temp)){
             qDebug()<<studentObj[temp];
         }
     }

     studentObj.empty();

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
      sampleStudent->runCommand("h");
       a.quit();
       return 0;
    }


    a.quit();
    return 0;
}
