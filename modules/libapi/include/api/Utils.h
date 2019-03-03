#pragma once

#include <functional>

#include <QString>
#include <cpprest/details/basic_types.h>

namespace api
{
namespace utils
{

void ExecuteOnMainThread(const std::function<void(void)> func, const bool isSync);
bool IsMainThread();

utility::string_t QStringToStringT(const QString& str);
QString StringTToQString(const utility::string_t& str);

template<typename T>
utility::string_t ToStringT(const T& value)
{
#ifdef _UTF16_STRINGS
	return std::to_wstring(value);
#else
	return std::to_string(value);
#endif
}

} // namespace utils
} // namespace api
