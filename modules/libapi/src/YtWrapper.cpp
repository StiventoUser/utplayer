#include <QDesktopServices>
#include <QDebug>
#include <QFileInfo>
#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <fstream>

#include "api/YtWrapper.h"

namespace api
{

OAuth2YtSession::OAuth2YtSession(utility::string_t clientKey, utility::string_t clientSecret,
	utility::string_t authEndpoint, utility::string_t tokenEndpoint, utility::string_t redirectUri, utility::string_t refreshToken)
	: OAuth2Session(U("Youtube"),
		clientKey,
		clientSecret,
		authEndpoint,
		tokenEndpoint,
		redirectUri,
		refreshToken)
{
	oauth2Config_.set_scope(
		U(
			"https://www.googleapis.com/auth/youtube" " "
			"https://www.googleapis.com/auth/youtube.force-ssl" " "
			"https://www.googleapis.com/auth/youtube.readonly" " "
			"https://www.googleapis.com/auth/youtubepartner"));
}

void OAuth2YtSession::RunInternal()
{
	std::wofstream ofs(L"test.txt");
	auto t = httpConfig_.oauth2()->token();
	ofs << httpConfig_.oauth2()->token().refresh_token() << std::flush;

	web::http::client::http_client api(U("https://www.googleapis.com/"), httpConfig_);
	qDebug() << "Requesting account information:\n"
		<< "Information: " << api.request(web::http::methods::GET, U("/youtube/v3/videos?part=snippet,contentDetails,statistics&chart=mostPopular")).get().extract_string().get();
}

YtWrapper::YtWrapper(QObject* parent)
	: QObject(parent)
{

}

void YtWrapper::Authorize()
{
	QFileInfo check_file("test.txt");

	std::wstring refreshToken;
	if (check_file.exists() && check_file.isFile())
	{
		std::wifstream ifs("test.txt");
		ifs >> refreshToken;
	}

	ytSession_ = std::make_unique<OAuth2YtSession>(
		clientId_.toStdWString(),
		clientSecret_.toStdWString(),
		authUri_.toString().toStdWString(),
		tokenUri_.toString().toStdWString(),
		redirectUri_.toString().toStdWString(),
		refreshToken);

	qDebug() << "Authorizing...";
	ytSession_->Run();
}

QUrl YtWrapper::GetAuthUri() const
{
	return authUri_;
}

QString YtWrapper::GetClientId() const
{
	return clientId_;
}

QString YtWrapper::GetClientSecret() const
{
	return clientSecret_;
}

QUrl YtWrapper::GetRedirectUri() const
{
	return redirectUri_;
}

QUrl YtWrapper::GetTokenUri() const
{
	return tokenUri_;
}

void YtWrapper::SetAuthUri(const QUrl& authUri)
{
	if (authUri_ == authUri) {
		return;
	}

	authUri_ = authUri;
	emit authUriChanged(authUri_);
}

void YtWrapper::SetClientId(const QString& clientId)
{
	if (clientId_ == clientId) {
		return;
	}

	clientId_ = clientId;
	emit clientIdChanged(clientId_);
}

void YtWrapper::SetClientSecret(const QString& clientSecret)
{
	if (clientSecret_ == clientSecret) {
		return;
	}

	clientSecret_ = clientSecret;
	emit clientSecretChanged(clientSecret_);
}

void YtWrapper::SetRedirectUri(const QUrl& redirectUri)
{
	if (redirectUri_ == redirectUri) {
		return;
	}

	redirectUri_ = redirectUri;
	emit redirectUriChanged(redirectUri_);
}

void YtWrapper::SetTokenUri(const QUrl& tokenUri)
{
	if (tokenUri_ == tokenUri) {
		return;
	}

	tokenUri_ = tokenUri;
	emit tokenUriChanged(authUri_);
}

}
