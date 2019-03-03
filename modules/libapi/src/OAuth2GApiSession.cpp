#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>
#include <QDebug>

#include "api/OAuth2GApiSession.h"

namespace api
{

OAuth2GApiSession::OAuth2GApiSession(utility::string_t clientKey, utility::string_t clientSecret,
	utility::string_t authEndpoint, utility::string_t tokenEndpoint, utility::string_t redirectUri, utility::string_t refreshToken)
	: OAuth2Session(_XPLATSTR("Youtube"),
		clientKey,
		clientSecret,
		authEndpoint,
		tokenEndpoint,
		redirectUri,
		refreshToken)
{
	oauth2Config_.set_scope(
		_XPLATSTR(
			"https://www.googleapis.com/auth/youtube" " "
			"https://www.googleapis.com/auth/youtube.force-ssl" " "
			"https://www.googleapis.com/auth/youtube.readonly" " "
			"https://www.googleapis.com/auth/youtubepartner"));
}

void OAuth2GApiSession::RunInternal()
{
	//std::wofstream ofs(L"test.txt");
	//auto t = httpConfig_.oauth2()->token();
	//ofs << httpConfig_.oauth2()->token().refresh_token() << std::flush;

	web::http::client::http_client api(_XPLATSTR("https://www.googleapis.com/"));
	qDebug() << "Requesting account information:\n"
		<< "Information: " << api.request(web::http::methods::GET, _XPLATSTR("/youtube/v3/videos?part=snippet,contentDetails,statistics&chart=mostPopular&key=")).get().extract_string().get();
}

}
