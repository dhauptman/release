#include "terminalmainwindow.h"
#include "ui_terminalmainwindow.h"
#include "terminalconsole.h"
#include "terminalsettingsdialog.h"
#include "wso100.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>

TerminalMainWindow::TerminalMainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::TerminalMainWindow)
{
    ui->setupUi(this);
	console = new TerminalConsole;
    wso = new wso100;
	wso->setAllowedAreas(Qt::RightDockWidgetArea);
	//wso->setWidget(wso);
	addDockWidget(Qt::RightDockWidgetArea, wso);
	tabifiedDockWidgets(wso);
    console->setEnabled(false);
    setCentralWidget(console);
    serial = new QSerialPort(this);
    settings = new TerminalSettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    initActionsConnections();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(console, SIGNAL(getData(QByteArray)), this, SLOT(writeData(QByteArray)));
}

TerminalMainWindow::~TerminalMainWindow()
{
    delete settings;
    delete ui;
}

void TerminalMainWindow::openSerialPort()
{
    TerminalSettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            console->setEnabled(true);
            console->setLocalEchoEnabled(p.localEchoEnabled);
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }

}

void TerminalMainWindow::closeSerialPort()
{
    serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void TerminalMainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

void TerminalMainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void TerminalMainWindow::readData()
{
    QByteArray data = serial->readAll();
    console->putData(data);
    wso->pushData();
}


void TerminalMainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void TerminalMainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
