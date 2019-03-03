#include "api/ApiRequest.h"

namespace api
{

ApiRequest::ApiRequest(const utility::string_t& url) : url_(url)
{
}

utility::string_t ApiRequest::GenerateRequestString() const
{
	return url_;
}

} // namespace api
