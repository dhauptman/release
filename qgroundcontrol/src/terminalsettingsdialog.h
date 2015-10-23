#ifndef TERMINALSETTINGSDIALOG
#define TERMINALSETTINGSDIALOG

#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_USE_NAMESPACE

namespace Ui
{
class TerminalSettingsDialog;
}

class QIntValidator;

class TerminalSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    explicit TerminalSettingsDialog(QWidget *parent = 0);
    ~TerminalSettingsDialog();

    Settings settings() const;

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();
private:
    Ui::TerminalSettingsDialog *ui;
    Settings currentSettings;
    QIntValidator *intValidator;
};

#endif // TERMINALSETTINGSDIALOG

