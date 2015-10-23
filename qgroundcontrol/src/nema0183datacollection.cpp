#include "nema0183datacollection.h"

QString Nema0183DataCollection::ATMOS_DATA("");
QString Nema0183DataCollection::MVW_Data("");
QString Nema0183DataCollection::OUTSIDE_H_Data("");
QString Nema0183DataCollection::OUTSIDE_T_Data("");

Nema0183DataCollection::Nema0183DataCollection(QWidget *parent)
{
}

QString Nema0183DataCollection::get_MVW_Data()
{
    return MVW_Data;
}

void Nema0183DataCollection::set_MVW_Data(const QString &value)
{
    MVW_Data = value;
}

QString Nema0183DataCollection::get_OUTSIDE_H_Data()
{
    return OUTSIDE_H_Data;
}

void Nema0183DataCollection::set_OUTSIDE_H_Data(const QString &value)
{
    OUTSIDE_H_Data = value;
}

QString Nema0183DataCollection::get_OUTSIDE_T_Data()
{
    return OUTSIDE_T_Data;
}

void Nema0183DataCollection::set_OUTSIDE_T_Data(const QString &value)
{
    OUTSIDE_T_Data = value;
}

QString Nema0183DataCollection::get_ATMOS_DATA()
{
    return ATMOS_DATA;
}

void Nema0183DataCollection::set_ATMOS_DATA(const QString &value)
{
    ATMOS_DATA = value;
}
