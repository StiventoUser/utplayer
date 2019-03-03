#pragma once

#include <QObject>
#include <QString>
#include <QUrl>

namespace api
{

class GApiAccessData
	: public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString accessKey READ getAccessKey WRITE setAccessKey NOTIFY accessKeyChanged)
	Q_PROPERTY(QUrl authUri READ getAuthUri WRITE setAuthUri NOTIFY authUriChanged)
	Q_PROPERTY(QString clientId READ getClientId WRITE setClientId NOTIFY clientIdChanged)
	Q_PROPERTY(QString clientSecret READ getClientSecret WRITE setClientSecret NOTIFY clientSecretChanged)
	Q_PROPERTY(QUrl redirectUri READ getRedirectUri WRITE setRedirectUri NOTIFY redirectUriChanged)
	Q_PROPERTY(QUrl tokenUri READ getTokenUri WRITE setTokenUri NOTIFY tokenUriChanged)

public:
	GApiAccessData(QObject* parent = nullptr);

signals:
	void accessKeyChanged(QString);
	void authUriChanged(QUrl);
	void clientIdChanged(QString);
	void clientSecretChanged(QString);
	void redirectUriChanged(QUrl);
	void tokenUriChanged(QUrl);

public slots:
	QString getAccessKey() const;
	QUrl getAuthUri() const;
	QString getClientId() const;
	QString getClientSecret() const;
	QUrl getRedirectUri() const;
	QUrl getTokenUri() const;

	void setAccessKey(const QString& key);
	void setAuthUri(const QUrl& authUri);
	void setClientId(const QString& clientId);
	void setClientSecret(const QString& clientSecret);
	void setRedirectUri(const QUrl& redirectUri);
	void setTokenUri(const QUrl& tokenUri);

private:
	QString accessKey_;
	QUrl authUri_;
	QString clientId_;
	QString clientSecret_;
	QUrl redirectUri_;
	QUrl tokenUri_;
};

}
