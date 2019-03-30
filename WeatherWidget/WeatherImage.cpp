#include "WeatherImage.h"



WeatherImage::WeatherImage()
{
}

WeatherImage::WeatherImage(int ID, QDateTime time, QTime sunrise, QTime sunset)
{
	this->ID = ID;
	this->time = time;
	this->sunrise = sunrise;
	this->sunset = sunset;
	if (ID / 100 == 2)
		pixmap.load(":/WeatherWidget/Resources/Thunderstorm.png");
	else if (ID / 100 == 3)
		pixmap.load(":/WeatherWidget/Resources/Rain.png");
	else if (ID / 100 == 5)
	{
		if (ID >= 500 && ID <= 504)
			pixmap.load(":/WeatherWidget/Resources/SunRain.png");
		else
			pixmap.load(":/WeatherWidget/Resources/MoonRain.png");
	}
	else if (ID / 100 == 6)
		pixmap.load(":/WeatherWidget/Resources/Snow.png");
	else if (ID / 100 == 7)
		pixmap.load(":/WeatherWidget/Resources/Mist.png");
	else if (ID == 800)
	{
		if(time.time()>=sunrise && time.time()<sunset)
			pixmap.load(":/WeatherWidget/Resources/Sun.png");
		else
			pixmap.load(":/WeatherWidget/Resources/Moon.png");
	}
	else if (ID / 10 == 80)
	{
		if (ID == 801)
		{
			if (time.time() >= sunrise && time.time() < sunset)
				pixmap.load(":/WeatherWidget/Resources/SunWithClouds.png");
			else
				pixmap.load(":/WeatherWidget/Resources/MoonWithClouds.png");
		}
		else if (ID == 802)
			pixmap.load(":/WeatherWidget/Resources/Cloud.png");
		else if (ID == 803 || ID == 804)
			pixmap.load(":/WeatherWidget/Resources/DarkCloud.png");
	}
}


WeatherImage::~WeatherImage()
{
}
