#include <QDebug>
#include <QFileInfo>
#include <cpprest/http_client.h>
#include <fstream>

#include "api/GApiAccessData.h"
#include "api/GApiWrapper.h"
#include "api/OAuth2GApiSession.h"
#include "api/Utils.h"

namespace api
{

GApiWrapper::GApiWrapper(QObject* parent) : QObject(parent)
{
}

void GApiWrapper::authorize()
{
	if (!accessData_)
	{
		qCritical() << "Access data is empty";
	}

	QFileInfo check_file("test.txt");

	std::wstring refreshToken;
	if (check_file.exists() && check_file.isFile())
	{
		std::wifstream ifs("test.txt");
		ifs >> refreshToken;
	}

	ytSession_ = std::make_unique<OAuth2GApiSession>(
		utils::QStringToStringT(accessData_->getClientId()),
		utils::QStringToStringT(accessData_->getClientSecret()),
		utils::QStringToStringT(accessData_->getAuthUri().toString()),
		utils::QStringToStringT(accessData_->getTokenUri().toString()),
		utils::QStringToStringT(accessData_->getRedirectUri().toString()),
		refreshToken);

	qDebug() << "Authorizing...";
	ytSession_->Run();
}

ApiResponse GApiWrapper::requestPublicData(const ApiRequest& request) const
{
	if (!accessData_)
	{
		qCritical() << "Data to access the service is null.";
		return {};
	}

	web::http::client::http_client api(baseApiUrl_);

	auto requestString = request.GenerateRequestString();
	requestString += _XPLATSTR("&key=") + utils::QStringToStringT(accessData_->getAccessKey());

	qDebug() << "Requesting as public: " << requestString;

	auto response = api.request(web::http::methods::GET, requestString)
						.then([](web::http::http_response& resp) {
							qDebug() << "Got public response: " << resp.status_code();

							return resp.extract_string();
						})
						.then([](utility::string_t& text) {
							ApiResponse response;
							response.SetText(text);

							return response;
						})
						.get();

	return response;
}

GApiAccessData* GApiWrapper::getAccessData() const
{
	return accessData_;
}

void GApiWrapper::setAccessData(GApiAccessData* data)
{
	if (accessData_ == data)
	{
		return;
	}

	accessData_ = data;
	emit accessDataChanged(accessData_);
}

} // namespace api
