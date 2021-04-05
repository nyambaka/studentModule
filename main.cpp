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
#include<QList>
#include<QRegExp>
#include<QValidator>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<iostream>
#include<iostream>
#include"utility.h"
#include<QMap>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("student");
    QCoreApplication::setApplicationVersion("1.0.0");

    QJsonObject studentData= QJsonObject();
    QJsonObject result = QJsonObject();

    QFile * studentTemp = new QFile(":/student/stu.json");
    if(!studentTemp->open(QFile::ReadOnly)){
        std::cout<<"could not open file for reading and writing";
        return 0;
    }

    utility * tempUtility = new utility();

    bool schemaRequested=false;

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

    QMap<QString,QString>selectOptions;
    selectOptions.insert("e","age");
    selectOptions.insert("c","class");
    selectOptions.insert("p","kcpe");
    selectOptions.insert("y","kcpeMark");
    selectOptions.insert("g","gender");
    selectOptions.insert("a","active");
    selectOptions.insert("d","code");
    selectOptions.insert("m","firstName");
    selectOptions.insert("n","secondName");
    selectOptions.insert("t","thirdName");
    selectOptions.insert("u","fourthName");
    selectOptions.insert("r","admissionNumber");

    QJsonObject deepSelectionOption = QJsonObject();
    QJsonObject deepSelectionOptionProvided = QJsonObject();
    QJsonObject limitAndOffsetProvided= QJsonObject();

    deepSelectionOption.insert("sO",QJsonArray()<<"sO"<<"streamViewOption"<<"sO"<<"00"<<"stream");
    deepSelectionOption.insert("jO",QJsonArray()<<"jO"<<"subjectViewOption"<<"jO"<<"00"<<"subject");
    deepSelectionOption.insert("cO",QJsonArray()<<"cO"<<"ClassViewOption"<<"cO"<<"00"<<"class");
    deepSelectionOption.insert("lO",QJsonArray()<<"lO"<<"lostBookViewOption"<<"lO"<<"00"<<"lostBook");
    deepSelectionOption.insert("fO",QJsonArray()<<"fO"<<"feesViewOption"<<"fO"<<"00"<<"gammu");

    foreach (QJsonValue val, deepSelectionOption){
        QJsonArray tempArray=val.toArray();
        parser.addOption(QCommandLineOption(tempArray[0].toString(),tempArray[1].toString(),tempArray[3].toString(),tempArray[3].toString()));
    }

    QJsonObject limitAndOffset= QJsonObject();

    limitAndOffset.insert("limit",QJsonArray()<<"limit"<<"limit"<<"limit"<<"50");
    limitAndOffset.insert("offset",QJsonArray()<<"offset"<<"offset"<<"offset"<<"0");

    foreach (QJsonValue val, limitAndOffset){
        QJsonArray tempArray=val.toArray();
        parser.addOption(QCommandLineOption(tempArray[0].toString(),tempArray[1].toString(),tempArray[3].toString(),tempArray[3].toString()));
    }

    parser.addOption(QCommandLineOption(selectOptions.keys()));


    QJsonObject UtilitOptions= QJsonObject();
    UtilitOptions.insert("schema","schema");

    parser.addOption(QCommandLineOption("schema"));

    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(a);

    QStringList options(parser.optionNames());
    bool hasErrors=false;
    QStringList selectOptionProvided,deepSelectionOptionkeys,limitAndOffsetkeys;
    deepSelectionOptionkeys=deepSelectionOption.keys();
    limitAndOffsetkeys= limitAndOffset.keys();

    foreach (QString providedOptions, options) {
        if(providedOptions.contains("schema")){
            schemaRequested=true;
        }

        if(selectOptions.contains(providedOptions)){
            selectOptionProvided.append(selectOptions.value(providedOptions));
            continue;
        }
        if(deepSelectionOptionkeys.contains(providedOptions)){
            deepSelectionOptionProvided.insert(deepSelectionOption.value(providedOptions).toArray()[4].toString(),parser.value(providedOptions));
            continue;
        }

        if(limitAndOffsetkeys.contains(providedOptions)){
            QRegularExpression rx("^\\d{1,15}$");
            QRegularExpressionMatch match= rx.match(parser.value(providedOptions));
            if(!match.hasMatch()){
                hasErrors=true;
                result.insert(providedOptions,providedOptions+" should be an interger");
                continue;
            }
            limitAndOffsetProvided.insert(limitAndOffset.value(providedOptions).toArray()[0].toString(),parser.value(providedOptions));
            continue;
        }
        if(!singleStudent::validate(parser.value(providedOptions),studentObj[providedOptions].toArray()[1].toString())){
            hasErrors=true;
            result.insert(providedOptions,studentObj[providedOptions].toArray()[8].toString());
        }
        else{
            studentData.insert(providedOptions,parser.value(providedOptions));
        }
    }

    if(!hasErrors){
        if(schemaRequested){
            QJsonObject studentSchema{};
            foreach (auto key, studentObj) {
                studentSchema.insert(key.toArray()[4].toString(),key.toArray()[1].toVariant().toString());
            }
            studentSchema.remove("");
            QJsonDocument doc= QJsonDocument(studentSchema);
            std::cout<<doc.toJson(QJsonDocument::JsonFormat::Compact).toStdString();

        }else{
            singleStudent tempStudent (studentData);
            QObject::connect(&tempStudent,singleStudent::quit,&a,QCoreApplication::quit);
            tempStudent.connectToMysqlDatabase();
            tempStudent.mysqlSelectQuery(selectOptionProvided,studentObj,deepSelectionOptionProvided,limitAndOffsetProvided);
            a.quit();
            return 0;
        }

    }else{
        result.insert("error","true");
        QJsonDocument doc= QJsonDocument(result);
        std::cout<<doc.toJson(QJsonDocument::JsonFormat::Compact).toStdString();


    }
    a.quit();
    return 0;
}
