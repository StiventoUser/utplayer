#include <cpprest/details/basic_types.h>
#include <cpprest/base_uri.h>
#include <cpprest/oauth2.h>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "api/OAuth2Session.h"

namespace api
{

OAuth2CodeListener::OAuth2CodeListener(web::uri listen_uri, web::http::oauth2::experimental::oauth2_config& config)
	: listener_(new web::http::experimental::listener::http_listener(listen_uri))
	, config_(config)
{
	listener_->support([this](web::http::http_request request)
	{
		if (request.request_uri().path() == _XPLATSTR("/") && request.request_uri().query() != _XPLATSTR(""))
		{
			std::unique_lock<std::mutex> lock(resplock_);

			config_.token_from_redirected_uri(request.request_uri())
				.then([this, request](pplx::task<void> token_task)
				{
					try
					{
						token_task.wait();
						tce_.set(true);
					}
					catch (const web::http::oauth2::experimental::oauth2_exception& e)
					{
						qCritical() << "Error: " << e.what();
						tce_.set(false);
					}
			});

			request.reply(web::http::status_codes::OK, _XPLATSTR("Ok."));
		}
		else
		{
			request.reply(web::http::status_codes::NotFound, _XPLATSTR("Not found."));
		}
	});

	listener_->open().wait();
}

OAuth2CodeListener::~OAuth2CodeListener()
{
	listener_->close().wait();
}

pplx::task<bool> OAuth2CodeListener::ListenForCode()
{
	return pplx::create_task(tce_);
}

OAuth2Session::OAuth2Session(
	utility::string_t name,
	utility::string_t client_key,
	utility::string_t client_secret,
	utility::string_t auth_endpoint,
	utility::string_t token_endpoint,
	utility::string_t redirect_uri,
	utility::string_t refreshToken)
	: oauth2Config_(client_key, client_secret, auth_endpoint, token_endpoint, redirect_uri)
	, name_(name)
	, listener_(new OAuth2CodeListener(redirect_uri, oauth2Config_))
{
	auto token = oauth2Config_.token();
	token.set_refresh_token(refreshToken);
	oauth2Config_.set_token(token);
}

void OAuth2Session::Run()
{
	if (IsEnabled())
	{
		qDebug() << "Running " << name_.c_str() << " session...";

		if (!oauth2Config_.token().is_valid_access_token())
		{
			if (!oauth2Config_.token().refresh_token().empty())
			{
				oauth2Config_.token_from_refresh().wait();
				httpConfig_.set_oauth2(oauth2Config_);
			}
			else
			{
				if (Authorize().get())
				{
					httpConfig_.set_oauth2(oauth2Config_);
				}
				else
				{
					qDebug() << "Authorization failed for " << name_.c_str() << ".";
					return;
				}
			}
		}

		RunInternal();
	}
	else
	{
		qDebug() << "Skipped " << name_.c_str()
			<< " session sample because app key or secret is empty.";
	}
}

pplx::task<bool> OAuth2Session::Authorize()
{
	open_browser_auth();
	return listener_->ListenForCode();
}

bool OAuth2Session::IsEnabled() const
{
	return !oauth2Config_.client_key().empty() && !oauth2Config_.client_secret().empty();
}

void OAuth2Session::open_browser_auth()
{
	auto auth_uri(oauth2Config_.build_authorization_uri(true));
	auth_uri += _XPLATSTR("&access_type=offline&approval_prompt=force");
	qDebug() << "Opening browser in URI:" <<  auth_uri;

	QDesktopServices::openUrl(QString::fromWCharArray(auth_uri.c_str()));
}

}
