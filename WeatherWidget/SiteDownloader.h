#pragma once

#include <QObject>
#include <QtCore>
#include <QtNetwork>
#include <QSSl>

class SiteDownloader : public QObject
{
	Q_OBJECT

public:
	SiteDownloader(QObject *parent);
	SiteDownloader(QUrl url, QObject *parent);
	~SiteDownloader();
	QByteArray getDownloadedData();
	void download(QUrl url);
private slots:
	void downloadFinished(QNetworkReply *reply);
	void showErrors(QNetworkReply::NetworkError code);
private:
	QNetworkAccessManager *manager;
	QNetworkReply *reply;
	QByteArray downloadedData;
	QUrl url;
signals:
	void downloaded();
};
