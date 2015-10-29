#ifndef TERMINALMAINWINDOW
#define TERMINALMAINWINDOW

#include <QtCore/QtGlobal>

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>

namespace Ui{
class TerminalMainWindow;
}

class TerminalConsole;
class TerminalSettingsDialog;
class wso100;

class TerminalMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TerminalMainWindow(QWidget *parent = 0);
    ~TerminalMainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    Ui::TerminalMainWindow *ui;
    TerminalConsole *console;
    TerminalSettingsDialog *settings;
    wso100 *wso;
    QSerialPort *serial;
};

#endif // TERMINALMAINWINDOW

