#ifndef NEMA0183DATACOLLECTION
#define NEMA0183DATACOLLECTION
#include <QtCore/QtDebug>
class Nema0183DataCollection
{
public:
    explicit Nema0183DataCollection(QWidget *parent = 0);
    QString get_MVW_Data_Speed();
    void set_MVW_Data_Speed(const QString &value);
    QString get_MVW_Data_Angle();
    void set_MVW_Data_Angle(const QString &value);
    QString get_OUTSIDE_H_Data();
    void set_OUTSIDE_H_Data(const QString &value);
    QString get_OUTSIDE_T_Data();
    void set_OUTSIDE_T_Data(const QString &value);
    QString get_ATMOS_DATA();
    void set_ATMOS_DATA(const QString &value);

private:
    static QString MVW_Data_Speed;
    static QString MVW_Data_Angle;
    static QString OUTSIDE_H_Data;
    static QString OUTSIDE_T_Data;
    static QString ATMOS_DATA;
};

#endif // NEMA0183DATACOLLECTION

