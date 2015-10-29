#include "terminalparser.h"
#include "nema0183datacollection.h"
#include <QtCore/QtDebug>


QString TerminalParser::MVWNewString("");
QString TerminalParser::MVWOldString("");
QString TerminalParser::XDR_OUTSIDE_H_NewString("");
QString TerminalParser::XDR_OUTSIDE_H_OldString("");
QString TerminalParser::XDR_OUTSIDE_T_NewString("");
QString TerminalParser::XDR_OUTSIDE_T_OldString("");
QString TerminalParser::XDR_ATMOS_NewString("");
QString TerminalParser::XDR_ATMOS_OldString("");

Nema0183DataCollection dataCollector;

TerminalParser::TerminalParser(QWidget *parent)
	: QPlainTextEdit(parent)
	{
    }


bool TerminalParser::checkSumCalculation(QString data)
{
    data.chop(2);
    const char * arr = data.toUtf8();
    const char checkSumValue[2] = { arr[sizeof(arr) - 2], arr[sizeof(arr) - 1] };
    QString value = QString(checkSumValue);
    int i=0;
    quint16 checkSum = 0;
    for(i; i < sizeof(arr); i++)
    {
        if(arr[i] == '$')
        {
            //Do Nothing?
        }
        else if(arr[i] == '*')
        {
            break;
        }
        else
        {
            checkSum = checkSum ^ arr[i];
        }
    }

    bool * ok = false;
    if(checkSum == value.toInt(ok, 16))
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString TerminalParser::MVW_Parsing(QString data)
{
    if (data.contains("IIMWV"))
    {
        data = MVWOldString;
    }
    MVWNewString = data;
	//dataCollector.set_MVW_Data(MVWNewString);

    QString parsedString;
    QRegExp rx("[,]");
    QList<QString> list = data.split(rx, QString::KeepEmptyParts);

    int numberOfElements = 4;
    int missingElements = numberOfElements - list.length();
    for (int i = 0; i < missingElements; i++)
    {
        list.append("Null value");
    }

    parsedString = "Wind Speed and angle:\n";
    parsedString += "   Angle: " + list.at(0) + " degrees\n";
    parsedString += "   Reference: " + list.at(1) + "\n";
    parsedString += "   Wind Speed: " + list.at(2) + " " + list.at(3) + "\n";
    parsedString += "   Status: " + list.at(3) + "\n";

    dataCollector.set_MVW_Data_Angle(list.at(0));
    dataCollector.set_MVW_Data_Speed(list.at(2));
    MVWOldString = MVWNewString;

    return(parsedString);

}

QString TerminalParser::XDR_OUTSIDE_T_Parsing(QString data)
{
    QString tempString;
    if (data.contains("IIXDR"))
    {
        data = XDR_OUTSIDE_T_OldString;
    }
    XDR_OUTSIDE_T_NewString = data;
	//dataCollector.set_OUTSIDE_T_Data(XDR_OUTSIDE_T_NewString);

    tempString = XDR_OUTSIDE_T_NewString;
    QString parsedString;
    QRegExp rx ("[,]");
    QStringList list = tempString.split(rx, QString::KeepEmptyParts);


    int numberOfElements = 4;
    int missingElements = numberOfElements - list.length();
    for (int i = 0; i < missingElements; i++)
    {
        list.append("Null value");
    }

    parsedString = "Transducer Measurement:\n";
    parsedString += "   Transducer Type: " + list.at(0) + "\n";
    parsedString += "   Measurement Data: " + list.at(1) + "\n";
    parsedString += "   Units of measurement: " + list.at(2) + "\n";
    parsedString += "   Name of transducer: " + list.at(3) + "\n";

	dataCollector.set_OUTSIDE_T_Data(list.at(1));

    XDR_OUTSIDE_T_OldString = XDR_OUTSIDE_T_NewString ;
    return(parsedString);



}
QString TerminalParser::XDR_OUTSIDE_H_Parsing(QString data)
{
    QString tempString;
    if (data.contains("IIXDR"))
    {
        data = XDR_OUTSIDE_H_OldString;
    }
    XDR_OUTSIDE_H_NewString = data;
	//dataCollector.set_OUTSIDE_H_Data(XDR_OUTSIDE_H_NewString);

    tempString = XDR_OUTSIDE_H_NewString;
    QString parsedString;
    QRegExp rx ("[,]");
    QStringList list = tempString.split(rx, QString::KeepEmptyParts);


    int numberOfElements = 4;
    int missingElements = numberOfElements - list.length();
    for (int i = 0; i < missingElements; i++)
    {
        list.append("Null value");
    }

    parsedString = "Transducer Measurement:\n";
    parsedString += "   Transducer Type: " + list.at(0) + "\n";
    parsedString += "   Measurement Data: " + list.at(1) + "\n";
    parsedString += "   Units of measurement: " + list.at(2) + "\n";
    parsedString += "   Name of transducer: " + list.at(3) + "\n";

	dataCollector.set_OUTSIDE_H_Data(list.at(1));

    XDR_OUTSIDE_H_OldString = XDR_OUTSIDE_H_NewString;
    return(parsedString);



}
QString TerminalParser::XDR_ATMOS_Parsing(QString data)
{
    QString tempString;
    if (data.contains("IIXDR"))
    {
        data = XDR_ATMOS_OldString;
    }
    XDR_ATMOS_NewString = data;
	//dataCollector.set_ATMOS_DATA(XDR_ATMOS_NewString);

    tempString = XDR_ATMOS_NewString;
    QString parsedString;
    QRegExp rx ("[,]");
    QStringList list = tempString.split(rx, QString::KeepEmptyParts);


    int numberOfElements = 4;
    int missingElements = numberOfElements - list.length();
    for (int i = 0; i < missingElements; i++)
    {
        list.append("Null value");
    }

    parsedString = "Transducer Measurement:\n";
    parsedString += "   Transducer Type: " + list.at(0) + "\n";
    parsedString += "   Measurement Data: " + list.at(1) + "\n";
    parsedString += "   Units of measurement: " + list.at(2) + "\n";
    parsedString += "   Name of transducer: " + list.at(3) + "\n";

	dataCollector.set_ATMOS_DATA(list.at(1));

    XDR_ATMOS_OldString = XDR_ATMOS_NewString;
    return(parsedString);



}

QString TerminalParser::XDR_ATMOS_OUTAIR_Parsing(QString data)
{
    int wrongParseIndex = 0;
    QString parsedString;
    QRegExp rx ("[,]");
    QStringList list = data.split(rx, QString::KeepEmptyParts);
    wrongParseIndex =  list.indexOf("IIXDR", 0);
    if(wrongParseIndex != -1)
    {
        list.removeAt(wrongParseIndex);
    }
    parsedString = "Transducer Measurement:\n";
    for (int i = 0; i < list.length() - 3; i += 4)
    {
        parsedString += "   Transducer Type: " + list.at(i) + "\n";
        parsedString += "   Measurement Data: " + list.at(i + 1) + "\n";
        parsedString += "   Units of measurement: " + list.at(i + 2) + "\n";
        if (list.at(i + 3).contains("ATMOS") || list.at(i + 3).contains("WATER") || list.at(i + 3).contains("OUTAIR"))
        {
            parsedString += "   Name of transducer: " + list.at(i + 3) + "\n";
        }
    }
    return(parsedString);
}

QString TerminalParser::XDR_ATMOS_OUTSIDE_Parsing(QString data)
{
    int wrongParseIndex = 0;
    QString parsedString;
    QRegExp rx ("[,]");
    QStringList list = data.split(rx, QString::KeepEmptyParts);
    wrongParseIndex = list.indexOf("IIXDR", 0);
    if(wrongParseIndex != -1)
    {
        list.removeAt(wrongParseIndex);
    }
    parsedString = "Transducer Measurement:\n";
    for (int i = 0; i < list.length() - 3; i += 4)
    {
        parsedString += "   Transducer Type: " + list.at(i) + "\n";
        parsedString += "   Measurement Data: " + list.at(i + 1) + "\n";
        parsedString += "   Units of measurement: " + list.at(i + 2) + "\n";
        if (list.at(i + 3).contains("ATMOS") || list.at(i + 3).contains("ENV_OUTSIDE_T") || list.at(i + 3).contains("ENV_OUTSIDE_H"))
        {
            parsedString += "   Name of transducer: " + list.at(i + 3) + "\n";
        }
    }
    return(parsedString);
}

