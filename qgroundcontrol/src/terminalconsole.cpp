#include "terminalconsole.h"
#include "terminalparser.h"
#include <QScrollBar>
#include <QRegExp>

#include <QtCore/QtDebug>

TerminalConsole::TerminalConsole(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(false)
    , totalString("")
    , MVWString("")
    , XDR_OUTSIDE_T_string("")
    , XDR_OUTSIDE_H_string("")
    , XDR_ATMOS_String("")
    , XDR_ATMOS_OUTSIDE_T_OUTSIDE_H_string("")
    , XDR_ATMOS_OUTAIR_T_WATER_T_string("")
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
}
/* Debugging, Dustin Hauptman
bool TerminalConsole::checkSumCalculation(QString data)
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
*/

void TerminalConsole::putData(const QByteArray &data)
{
    //Dustin Hauptman
	TerminalParser parser;
    QString DataString = QString(data);
    if(TerminalParser::checkSumCalculation(DataString))
    {
		//MVW Alone
        if(DataString.contains("IIMWV"))
        {
            DataString = DataString.remove(0, 7);
            DataString.chop(5);
			MVWString = parser.MVW_Parsing(DataString);
        }
		//Outside_T alone
        else if(DataString.contains("IIXDR") && DataString.contains("ENV_OUTSIDE_T") && !(DataString.contains("ENV_ATMOS_P")))
        {
            DataString = DataString.remove(0, 7);
            DataString.chop(5);
			XDR_OUTSIDE_T_string = parser.XDR_OUTSIDE_T_Parsing(DataString);
        }
		//Outside_H alone
        else if(DataString.contains("IIXDR") && DataString.contains("ENV_OUTSIDE_H") && !(DataString.contains("ENV_ATMOS_P")))
        {
            DataString = DataString.remove(0, 7);
            DataString.chop(5);
			XDR_OUTSIDE_H_string = parser.XDR_OUTSIDE_H_Parsing(DataString);
        }
		//Atmos_p alone
        else if(DataString.contains("IIXDR") && DataString.contains("ENV_ATMOS_P") && !(DataString.contains("ENV_OUTAIR_T") || DataString.contains("ENV_WATER_T") || DataString.contains("ENV_OUTSIDE_T")))
        {
            DataString = DataString.remove(0, 7);
            DataString.chop(5);
			XDR_ATMOS_String = parser.XDR_ATMOS_Parsing(DataString);
        }
        else if(DataString.contains("IIXDR") && DataString.contains("ENV_OUTSIDE_T") && DataString.contains("ENV_OUTSIDE_H") && DataString.contains("ENV_ATMOS_P") )
        {
            DataString = DataString.remove(0, 7);
            DataString.chop(5);
			XDR_ATMOS_OUTSIDE_T_OUTSIDE_H_string = parser.XDR_ATMOS_OUTSIDE_Parsing(DataString);
        }
        else if(DataString.contains("IIXDR") && DataString.contains("ENV_ATMOS_P") && DataString.contains("ENV_OUTAIR_T") && DataString.contains("ENV_WATER_T") )
        {
            DataString = DataString.remove(0, 7);
            DataString.chop(5);
			XDR_ATMOS_OUTAIR_T_WATER_T_string = parser.XDR_ATMOS_OUTAIR_Parsing(DataString);
        }

        totalString = MVWString + XDR_OUTSIDE_T_string + XDR_OUTSIDE_H_string + XDR_ATMOS_String + XDR_ATMOS_OUTSIDE_T_OUTSIDE_H_string + XDR_ATMOS_OUTAIR_T_WATER_T_string;
        setPlainText(totalString);
    }

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}
/* Debug, Dustin Hauptman
QString TerminalConsole::MVW_Parsing(QString data)
{
    if (data.contains("IIMWV"))
    {
        data = MVWOldString;
    }
    MVWNewString = data;

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

    MVWOldString = MVWNewString;

    return(parsedString);

}

QString TerminalConsole::XDR_OUTSIDE_T_Parsing(QString data)
{
	QString tempString;
    if (data.contains("IIXDR"))
    {
        data = XDR_OUTSIDE_T_OldString;
    }
	XDR_OUTSIDE_T_NewString = data;
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

    XDR_OUTSIDE_T_OldString = XDR_OUTSIDE_T_NewString ;
    return(parsedString);



}
QString TerminalConsole::XDR_OUTSIDE_H_Parsing(QString data)
{
	QString tempString;
    if (data.contains("IIXDR"))
    {
        data = XDR_OUTSIDE_H_OldString;
    }
    XDR_OUTSIDE_H_NewString = data;
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

    XDR_OUTSIDE_H_OldString = XDR_OUTSIDE_H_NewString;
    return(parsedString);



}
QString TerminalConsole::XDR_ATMOS_Parsing(QString data)
{
	QString tempString;
    if (data.contains("IIXDR"))
    {
        data = XDR_ATMOS_OldString;
    }
    XDR_ATMOS_NewString = data;
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

    XDR_ATMOS_OldString = XDR_ATMOS_NewString;
    return(parsedString);



}

QString TerminalConsole::XDR_ATMOS_OUTAIR_Parsing(QString data)
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

QString TerminalConsole::XDR_ATMOS_OUTSIDE_Parsing(QString data)
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
*/

void TerminalConsole::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void TerminalConsole::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        if (localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());
    }
}

void TerminalConsole::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void TerminalConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void TerminalConsole::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
