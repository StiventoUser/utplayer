#pragma once

#include <QObject>
#include <QString>
#include <QUrl>
#include <cpprest/details/basic_types.h>
#include <memory>

#include "api/ApiRequest.h"
#include "api/ApiResponse.h"
#include "api/OAuth2GApiSession.h"

namespace api
{

class ApiRequest;
class OAuth2GApiSession;
class GApiAccessData;

class GApiWrapper : public QObject
{
	Q_OBJECT

	Q_PROPERTY(
		GApiAccessData* accessData READ getAccessData WRITE setAccessData NOTIFY accessDataChanged)

public:
	GApiWrapper(QObject* parent = nullptr);

signals:
	void accessDataChanged(GApiAccessData*);

	void accessGranted();
	void accessError(const QString& error, const QString& errorDescription, const QUrl& uri);

public slots:
	GApiAccessData* getAccessData() const;

	void setAccessData(GApiAccessData* data);

	void authorize();
	// ApiResponse RequestAsUser(const ApiRequest& request);
	ApiResponse requestPublicData(const ApiRequest& request) const;

private:
	const wchar_t* baseApiUrl_ = _XPLATSTR("https://www.googleapis.com/");

	GApiAccessData* accessData_ = nullptr;
	std::unique_ptr<OAuth2GApiSession> ytSession_;
};

} // namespace api
