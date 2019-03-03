#include "api/ApiResponse.h"

namespace api
{

utility::string_t ApiResponse::GetText() const
{
	return text_;
}

void ApiResponse::SetText(utility::string_t text)
{
	text_ = text;
}

}
