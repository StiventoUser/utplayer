#pragma once

#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>

//using namespace utility;
//using namespace web;
//using namespace web::http;
//using namespace web::http::client;
//using namespace web::http::oauth2::experimental;
//using namespace web::http::experimental::listener;

namespace api
{

class OAuth2CodeListener
{
public:
	OAuth2CodeListener(web::uri listenUri, web::http::oauth2::experimental::oauth2_config& config);
	~OAuth2CodeListener();

public:
	pplx::task<bool> ListenForCode();

private:
	std::unique_ptr<web::http::experimental::listener::http_listener> listener_;
	pplx::task_completion_event<bool> tce_;
	web::http::oauth2::experimental::oauth2_config& config_;
	std::mutex resplock_;
};

class OAuth2Session
{
public:
	OAuth2Session(utility::string_t name,
		utility::string_t clientKey,
		utility::string_t clientSecret,
		utility::string_t authEndpoint,
		utility::string_t tokenEndpoint,
		utility::string_t redirectUri,
		utility::string_t refreshToken = _XPLATSTR(""));
	virtual ~OAuth2Session() = default;

	void Run();

protected:
	virtual void RunInternal() = 0;

	pplx::task<bool> Authorize();

	web::http::client::http_client_config httpConfig_;
	web::http::oauth2::experimental::oauth2_config oauth2Config_;

private:
	bool IsEnabled() const;

	void open_browser_auth();

	utility::string_t name_;
	std::unique_ptr<OAuth2CodeListener> listener_;
};

}
