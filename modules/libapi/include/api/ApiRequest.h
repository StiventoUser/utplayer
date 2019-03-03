#pragma once

#include <cpprest/details/basic_types.h>

namespace api
{

class ApiRequest
{
public:
	explicit ApiRequest(const utility::string_t& url);

public:
	utility::string_t GenerateRequestString() const;

private:
	utility::string_t url_;
};

}
