#include "SiteDownloader.h"
#include <QUrl>

SiteDownloader::SiteDownloader(QUrl url, QObject *parent)
	: QObject(parent), manager(new QNetworkAccessManager(this)), reply(nullptr), url(url)
{
	connect(manager, &QNetworkAccessManager::finished, this, &SiteDownloader::downloadFinished);
	QNetworkRequest request(url);
	reply = manager->get(request);
	connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &SiteDownloader::showErrors);
}

SiteDownloader::SiteDownloader(QObject *parent)
	: QObject(parent), manager(new QNetworkAccessManager(this)), reply(nullptr)
{
	connect(manager, &QNetworkAccessManager::finished, this, &SiteDownloader::downloadFinished);
}

void SiteDownloader::download(QUrl url)
{
	QNetworkRequest request(url);
	reply = manager->get(request);
	connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &SiteDownloader::showErrors);
	this->url = url;
}

SiteDownloader::~SiteDownloader()
{
}

void SiteDownloader::downloadFinished(QNetworkReply *reply)
{
	downloadedData = reply->readAll();
	(this->reply)->deleteLater();
	emit downloaded();
}

QByteArray SiteDownloader::getDownloadedData()
{
	return downloadedData;
}

void SiteDownloader::showErrors(QNetworkReply::NetworkError code)
{
	qDebug() << "Error:" << code;
}

