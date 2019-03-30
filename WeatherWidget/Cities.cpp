#include "Cities.h"
#include <QtCore>
#include <QtWidgets>
#include <QMessageBox>

City::City()
{
}

City::City(const QString& name, const QString& country, const QString& countryISO2, QPair<double, double> coord, unsigned int id)
{
	this->name = name;
	this->id = id;
	this->countryISO2 = countryISO2;
	this->coord = coord;
	this->country = country;
}

