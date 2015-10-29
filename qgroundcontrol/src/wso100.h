#ifndef WSO100
#define WSO100

#include <QtCore/QtGlobal>
#include <QDockWidget>
#include "nema0183datacollection.h"


namespace Ui{
class wso100;
}

class wso100 : public QDockWidget
{

public:
    explicit wso100(QWidget *parent = 0);
    ~wso100();
    void pushData();

private:
    Ui::wso100 *ui;
	Nema0183DataCollection *collector;
};



#endif // WSO100

