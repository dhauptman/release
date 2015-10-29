#include "wso100.h"
#include "ui_wso100.h"
#include "nema0183datacollection.h"

wso100::wso100(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::wso100)
{
	ui->setupUi(this);
}

wso100::~wso100()
{
	delete ui;
}

void wso100::pushData()
{
	ui.setData(blank);
}
