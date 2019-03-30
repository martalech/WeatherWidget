#pragma once

#include <QObject>
#include <QDateTime>
#include "WeatherImage.h"

class WeatherInfo
{
public:
	WeatherInfo();
	WeatherInfo(double temp, QString windDesc, double windSpeed, double windDir,QDateTime dt, double press
		, double hum, QTime sunrise, QTime sunset, int weatherID);
	~WeatherInfo();

	double getTemperature() { return temperature; }
	QString getDescriptrion() { return weatherDescription; }
	double getWindSpeed() { return windSpeed; }
	QString getWindDirection() { return windDirection; }
	QDateTime getDateTime() { return dateTime; }
	double getPressure() { return pressure; }
	double getHumidity() { return humidity; }
	QTime getSunrise() { return sunrise; }
	QTime getSunset() { return sunset; }
	int getWeatherID() { return weatherID; }
	QPixmap getWeatherImage() { return weatherImage.getPixmap(); }
private:
	double temperature;
	QString weatherDescription;
	double windSpeed;
	QString windDirection;
	QDateTime dateTime;
	double pressure;
	double humidity;
	QTime sunrise;
	QTime sunset;
	int weatherID;
	WeatherImage weatherImage;
};
