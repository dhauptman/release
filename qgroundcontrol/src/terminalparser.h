#ifndef TERMINALPARSER
#define TERMINALPARSER

#include <QplainTextEdit>

class TerminalParser : public QPlainTextEdit
{
	Q_OBJECT;

public:
    explicit TerminalParser(QWidget *parent = 0);

public:
    static QString MVW_Parsing(QString data);
    static QString XDR_OUTSIDE_H_Parsing(QString data);
    static QString XDR_OUTSIDE_T_Parsing(QString data);
    static QString XDR_ATMOS_Parsing(QString data);
    static QString XDR_ATMOS_OUTAIR_Parsing(QString data);
    static QString XDR_ATMOS_OUTSIDE_Parsing(QString data);
    static bool checkSumCalculation(QString data);
private:
	static QString MVWOldString;
	static QString MVWNewString;
	static QString XDR_OUTSIDE_H_OldString;
	static QString XDR_OUTSIDE_H_NewString;
	static QString XDR_OUTSIDE_T_OldString;
	static QString XDR_OUTSIDE_T_NewString;
	static QString XDR_ATMOS_OldString;
	static QString XDR_ATMOS_NewString;
};
#endif // TERMINALPARSER

