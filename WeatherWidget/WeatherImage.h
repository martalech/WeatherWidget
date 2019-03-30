#pragma once
#include <QtCore>
#include <QtGui>

class WeatherImage
{
public:
	WeatherImage();
	WeatherImage(int ID, QDateTime time, QTime sunrise, QTime sunset);
	~WeatherImage();

	QPixmap getPixmap() { return pixmap; }
private:
	QPixmap pixmap;
	int ID;
	QDateTime time;
	QTime sunrise;
	QTime sunset;
};

