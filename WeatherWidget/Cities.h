#pragma once

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtCore>
#include <QMap>

class City
{
	QString name;
	QString country;
	QString countryISO2;
	QPair<double, double> coord;
	unsigned int id;
public:
	City();
	City(const QString& name, const QString& country, const QString& countryISO2, QPair<double, double> coord, unsigned int id);

	QString getCountry() { return country; }
	unsigned int getId() { return id; }
	QString getName() { return name; }
	QPair<double, double> getCoord() { return coord; }
};
