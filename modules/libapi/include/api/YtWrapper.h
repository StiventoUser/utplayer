#pragma once

#include <QObject>
#include <QString>
#include <QUrl>
#include <memory>
#include "api/OAuth2Session.h"

namespace api
{

class OAuth2YtSession
	: public OAuth2Session
{
public:
	OAuth2YtSession(
		utility::string_t clientKey,
		utility::string_t clientSecret,
		utility::string_t authEndpoint,
		utility::string_t tokenEndpoint,
		utility::string_t redirectUri,
		utility::string_t refreshToken = _XPLATSTR(""));

protected:
	void RunInternal() override;
};

class YtWrapper
	: public QObject
{
	Q_OBJECT

	Q_PROPERTY(QUrl authUri READ GetAuthUri WRITE SetAuthUri NOTIFY authUriChanged)
	Q_PROPERTY(QString clientId READ GetClientId WRITE SetClientId NOTIFY clientIdChanged)
	Q_PROPERTY(QString clientSecret READ GetClientSecret WRITE SetClientSecret NOTIFY clientSecretChanged)
	Q_PROPERTY(QUrl redirectUri READ GetRedirectUri WRITE SetRedirectUri NOTIFY redirectUriChanged)
	Q_PROPERTY(QUrl tokenUri READ GetTokenUri WRITE SetTokenUri NOTIFY tokenUriChanged)

public:
	YtWrapper(QObject* parent = nullptr);

signals:
	void accessGranted();
	void accessError(const QString &error, const QString &errorDescription, const QUrl &uri);

	void authUriChanged(QUrl);
	void clientIdChanged(QString);
	void clientSecretChanged(QString);
	void redirectUriChanged(QUrl);
	void tokenUriChanged(QUrl);

public slots:
	void Authorize();

	QUrl GetAuthUri() const;
	QString GetClientId() const;
	QString GetClientSecret() const;
	QUrl GetRedirectUri() const;
	QUrl GetTokenUri() const;

	void SetAuthUri(const QUrl& authUri);
	void SetClientId(const QString& clientId);
	void SetClientSecret(const QString& clientSecret);
	void SetRedirectUri(const QUrl& redirectUri);
	void SetTokenUri(const QUrl& tokenUri);

private:
	std::unique_ptr<OAuth2YtSession> ytSession_;

	QUrl authUri_;
	QString clientId_;
	QString clientSecret_;
	QUrl redirectUri_;
	QUrl tokenUri_;
};

}
