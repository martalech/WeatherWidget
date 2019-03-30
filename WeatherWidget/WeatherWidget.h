#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WeatherWidget.h"
#include <QGeoPositionInfo>
#include "SiteDownloader.h"
#include "Cities.h"
#include "WeatherInfo.h"

class WeatherWidget : public QMainWindow
{
	Q_OBJECT

public:
	WeatherWidget(QWidget *parent = Q_NULLPTR);

private:
	Ui::WeatherWidgetClass ui;
	QUrl weatherUrl;
	QString weatherData;
	SiteDownloader* downloader;
	WeatherInfo currentWeatherInfo;
	QList<City> cityInfoList;
	QMap<QPair<QString, QString>, City> cityInfoMap;
	QStringList cityNames;
	City currentCity;

	void downloadData();
	void downloadCityInfo(const QString& path);
	void getWeatherInfo();
	QMap<QString, QString> downloadCountryNameMap(const QString& path);
private slots:
	void getCityInfo();
};
