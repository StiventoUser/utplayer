#pragma once

#include <cpprest/details/basic_types.h>

namespace api
{

class ApiResponse
{
public:
	utility::string_t GetText() const;
	void SetText(utility::string_t text);

private:
	utility::string_t text_;
};

}
