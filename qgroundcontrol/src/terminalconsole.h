#ifndef TERMINALCONSOLE
#define TERMINALCONSOLE

#include <QplainTextEdit>

class TerminalConsole : public QPlainTextEdit
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit TerminalConsole(QWidget *parent = 0);

    void putData(const QByteArray &data);

    void setLocalEchoEnabled(bool set);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    bool localEchoEnabled;
    QString MVWString;
    QString XDR_OUTSIDE_T_string;
    QString XDR_OUTSIDE_H_string;
    QString XDR_ATMOS_String;
    QString XDR_ATMOS_OUTSIDE_T_OUTSIDE_H_string;
    QString XDR_ATMOS_OUTAIR_T_WATER_T_string;
    QString totalString;
    //Debugging Dustin Hauptman
    //QString MVWOldString, MVWNewString;
    //QString XDR_OUTSIDE_H_OldString, XDR_OUTSIDE_H_NewString;
    //QString XDR_OUTSIDE_T_OldString, XDR_OUTSIDE_T_NewString;
    //QString XDR_ATMOS_OldString, XDR_ATMOS_NewString;
   };

#endif // TERMINALCONSOLE

