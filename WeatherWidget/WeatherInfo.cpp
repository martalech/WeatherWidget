#include "WeatherInfo.h"

WeatherInfo::WeatherInfo()
{
}

WeatherInfo::WeatherInfo(double temp, QString weatherDesc, double windSpeed, double windDir, QDateTime dt, double press
	, double hum, QTime sunrise, QTime sunset, int weatherID): weatherImage(weatherID, dt, sunrise, sunset)
{
	temperature = temp;
	weatherDescription = weatherDesc;
	weatherDescription[0] = weatherDescription[0].toUpper();
	this->windSpeed = windSpeed;
	if (windDir == 0)
		windDirection = "North";
	else if (windDir > 0 && windDir < 90)
		windDirection = "Northeast";
	else if (windDir == 90)
		windDirection = "East";
	else if (windDir > 90 && windDir < 180)
		windDirection = "Southeast";
	else if (windDir == 180)
		windDirection = "South";
	else if (windDir > 180 && windDir < 270)
		windDirection = "Southwest";
	else if (windDir == 270)
		windDirection = "West";
	else
		windDirection = "Northwest";
	dateTime = dt;
	pressure = press;
	humidity = hum;
	this->sunrise = sunrise;
	this->sunset = sunset;
	this->weatherID = weatherID;
}

WeatherInfo::~WeatherInfo()
{
}
