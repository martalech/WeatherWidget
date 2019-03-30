#include "WeatherWidget.h"
#include <QtCore>
#include <QtWidgets>

typedef QPair<QString, QString> NameCountry;
typedef QMap<NameCountry, City> CityMap;


WeatherWidget::WeatherWidget(QWidget *parent)
	: QMainWindow(parent), downloader(new SiteDownloader(this))
{
	ui.setupUi(this);
	downloadCityInfo(qApp->applicationDirPath() + "/city.list.json");
	connect(downloader, &SiteDownloader::downloaded, this, &WeatherWidget::downloadData);
	QCompleter *completer = new QCompleter(cityNames, this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setCompletionMode(QCompleter::InlineCompletion);
	ui.lineEdit->setCompleter(completer);
	connect(ui.lineEdit, &QLineEdit::editingFinished, this, &WeatherWidget::getCityInfo);
	for (int c = 0; c < ui.tableWidget->horizontalHeader()->count(); ++c)
	{
		ui.tableWidget->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
	}
	for (int c = 0; c < ui.tableWidget->verticalHeader()->count(); ++c)
	{
		ui.tableWidget->verticalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
	}
}

void WeatherWidget::downloadData()
{
	weatherData = downloader->getDownloadedData();
	getWeatherInfo();
	ui.label_2->setText(currentCity.getName() + ", " + currentCity.getCountry());
	ui.label_3->setText(currentWeatherInfo.getDateTime().toString());
	QChar degree(0x00B0);
	ui.tableWidget->setItem(0, 0, new QTableWidgetItem(QString::number(currentWeatherInfo.getTemperature()) + degree + 'C'));
	ui.tableWidget->setItem(1, 0, new QTableWidgetItem(currentWeatherInfo.getDescriptrion()));
	ui.tableWidget->setItem(2, 0, new QTableWidgetItem(QString::number(currentWeatherInfo.getWindSpeed()) 
		+ " m/s, " + currentWeatherInfo.getWindDirection()));
	ui.tableWidget->setItem(3, 0, new QTableWidgetItem(QString::number(currentWeatherInfo.getPressure()) + " hpa"));
	ui.tableWidget->setItem(4, 0, new QTableWidgetItem(QString::number(currentWeatherInfo.getHumidity()) + " %"));
	ui.tableWidget->setItem(5, 0, new QTableWidgetItem(currentWeatherInfo.getSunrise().toString()));
	ui.tableWidget->setItem(6, 0, new QTableWidgetItem(currentWeatherInfo.getSunset().toString()));
	ui.label_4->setPixmap(currentWeatherInfo.getWeatherImage().scaled(ui.label_4->size(), Qt::KeepAspectRatio));
}

void WeatherWidget::downloadCityInfo(const QString& path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		throw std::exception("Cannot open file.");
	}
	QString list;
	list = file.readAll();
	file.close();
	QJsonDocument jsonDocument = QJsonDocument::fromJson(list.toUtf8());
	QJsonArray jsonArray = jsonDocument.array();
	QVariantList variantList = jsonArray.toVariantList();
	QMap<QString, QString> countryNameMap = downloadCountryNameMap(qApp->applicationDirPath() + "/iso2tofull.json");
	for (auto it : variantList)
	{
		QJsonObject jsonObject = it.toJsonObject();
		QString name = jsonObject.value("name").toString();
		unsigned int id = jsonObject.value("id").toInt();
		QString countryISO2 = jsonObject.value("country").toString();
		QJsonObject coordObject = jsonObject.value("coord").toObject();
		QPair<double, double> coord;
		coord.first = coordObject.value("lon").toDouble();
		coord.second = coordObject.value("lat").toDouble();
		QString fullCountryName = countryNameMap.value(countryISO2);
		if (name != "" && name != "-" && countryISO2 != "" && countryISO2 != "-")
		{
			City city(name, fullCountryName, countryISO2, coord, id);
			cityInfoMap.insert(NameCountry(name, fullCountryName), city);
			cityInfoList += city;
			QString cityName = name + ", " + fullCountryName;
			cityNames += cityName;
		}
	}
	cityNames.sort();
}

QMap<QString, QString> WeatherWidget::downloadCountryNameMap(const QString& path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		throw std::exception("Cannot open file.");
	}
	QString list;
	list = file.readAll();
	file.close();
	QJsonDocument jsonDocument = QJsonDocument::fromJson(list.toUtf8());
	QJsonObject jsonObject = jsonDocument.object();
	QVariantMap variantMap = jsonObject.toVariantMap();
	QMap<QString, QString> countryNameMap;
	for (QVariantMap::const_iterator it = variantMap.begin(); it != variantMap.end(); ++it)
	{
		countryNameMap.insert(it.key(), it.value().toString());
	}
	return countryNameMap;
}

void WeatherWidget::getCityInfo()
{
	QString text = ui.lineEdit->text();
	QString name = text.section(", ", 0, 0);
	QString country = text.section(", ", -1);
	CityMap::const_iterator it;
	if ((it = cityInfoMap.find(NameCountry(name, country))) != cityInfoMap.end())
	{
		currentCity = *it;
		weatherUrl = QUrl("https://api.openweathermap.org/data/2.5/weather?id=" + QString::number(currentCity.getId()) + "&appid=bc2bd6a0b5e10846a99f6ba726c62741");
		downloader->download(weatherUrl);
	}
}

void WeatherWidget::getWeatherInfo()
{
	QJsonDocument jsonDocument = QJsonDocument::fromJson(weatherData.toUtf8());
	QJsonObject dataObject = jsonDocument.object();
	QJsonObject weather = dataObject.value("weather").toArray()[0].toObject();
		QString weatherDescription = weather.value("description").toString();
		int weatherID = weather.value("id").toInt();
	QJsonObject main = dataObject.value("main").toObject();
		double temp = main.value("temp").toDouble() - 273.15;
		double pressure = main.value("pressure").toDouble();
		double humidity = main.value("humidity").toDouble();
	QJsonObject wind = dataObject.value("wind").toObject();
		double windSpeed = wind.value("speed").toDouble();
		double windDirectionDegree = wind.value("deg").toDouble();
	QJsonObject clouds = dataObject.value("clouds").toObject();
		QDateTime local;
		local.setSecsSinceEpoch(dataObject.value("dt").toInt());
	QJsonObject sys = dataObject.value("sys").toObject();
		QDateTime sunriseDateTime, sunsetDateTime;
		sunriseDateTime.setSecsSinceEpoch(sys.value("sunrise").toInt());
		sunsetDateTime.setSecsSinceEpoch(sys.value("sunset").toInt());
		QTime sunriseTime, sunsetTime;
		sunriseTime = sunriseDateTime.time();
		sunsetTime = sunsetDateTime.time();
		currentWeatherInfo = WeatherInfo(temp, weatherDescription, windSpeed, windDirectionDegree, local, pressure, humidity, sunriseTime, sunsetTime, weatherID);
}



