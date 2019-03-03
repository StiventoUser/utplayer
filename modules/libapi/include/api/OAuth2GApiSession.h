#pragma once

#include <cpprest/details/basic_types.h>
#include "OAuth2Session.h"

namespace api
{

class OAuth2GApiSession
	: public OAuth2Session
{
public:
	OAuth2GApiSession(
		utility::string_t clientKey,
		utility::string_t clientSecret,
		utility::string_t authEndpoint,
		utility::string_t tokenEndpoint,
		utility::string_t redirectUri,
		utility::string_t refreshToken = _XPLATSTR(""));

protected:
	void RunInternal() override;
};

}
