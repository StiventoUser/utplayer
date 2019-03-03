#include "api/GApiAccessData.h"

namespace api
{

GApiAccessData::GApiAccessData(QObject* parent) : QObject(parent)
{
}

QString GApiAccessData::getAccessKey() const
{
	return accessKey_;
}

QUrl GApiAccessData::getAuthUri() const
{
	return authUri_;
}

QString GApiAccessData::getClientId() const
{
	return clientId_;
}

QString GApiAccessData::getClientSecret() const
{
	return clientSecret_;
}

QUrl GApiAccessData::getRedirectUri() const
{
	return redirectUri_;
}

QUrl GApiAccessData::getTokenUri() const
{
	return tokenUri_;
}

void GApiAccessData::setAccessKey(const QString& key)
{
	if (accessKey_ == key)
	{
		return;
	}

	accessKey_ = key;
	emit accessKeyChanged(accessKey_);
}

void GApiAccessData::setAuthUri(const QUrl& authUri)
{
	if (authUri_ == authUri)
	{
		return;
	}

	authUri_ = authUri;
	emit authUriChanged(authUri_);
}

void GApiAccessData::setClientId(const QString& clientId)
{
	if (clientId_ == clientId)
	{
		return;
	}

	clientId_ = clientId;
	emit clientIdChanged(clientId_);
}

void GApiAccessData::setClientSecret(const QString& clientSecret)
{
	if (clientSecret_ == clientSecret)
	{
		return;
	}

	clientSecret_ = clientSecret;
	emit clientSecretChanged(clientSecret_);
}

void GApiAccessData::setRedirectUri(const QUrl& redirectUri)
{
	if (redirectUri_ == redirectUri)
	{
		return;
	}

	redirectUri_ = redirectUri;
	emit redirectUriChanged(redirectUri_);
}

void GApiAccessData::setTokenUri(const QUrl& tokenUri)
{
	if (tokenUri_ == tokenUri)
	{
		return;
	}

	tokenUri_ = tokenUri;
	emit tokenUriChanged(authUri_);
}

} // namespace api
