#include "wso100.h"
#include "ui_wso100.h"
#include "nema0183datacollection.h"

wso100::wso100(QWidget *parent):
    ui(new Ui::wso100)
{
	ui->setupUi((QDialog*)this);
	collector = new Nema0183DataCollection;
}

wso100::~wso100()
{
	delete collector;
    delete ui;
}

void wso100::pushData()
{
	ui->ATMOSLineEdit->setText(collector->get_ATMOS_DATA());
	ui->outside_hLineEdit->setText(collector->get_OUTSIDE_H_Data());
	ui->outside_tLineEdit->setText(collector->get_OUTSIDE_T_Data());
    ui->windSpeedLineEdit->setText(collector->get_MVW_Data_Speed());
    ui->windAngleLineEdit->setText(collector->get_MVW_Data_Angle());
}
