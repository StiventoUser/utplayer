#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "ApiConfig.h"

#include "api/GApiAccessData.h"
#include "api/GApiCommandExecutor.h"
#include "api/GApiWrapper.h"
#include "api/UserProfile.h"
#include "api/commands/GetMostPopular.h"

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

	QGuiApplication app(argc, argv);

	QQuickStyle::setStyle("Universal");

	qRegisterMetaType<api::GApiAccessData*>("GApiAccessData*");
	qRegisterMetaType<api::GApiCommandExecutor*>("GApiCommandExecutor*");
	qRegisterMetaType<api::GApiWrapper*>("GApiWrapper*");
	qRegisterMetaType<api::UserProfile*>("UserProfile*");
	qRegisterMetaType<api::commands::Command*>("commands::Command*");
	qRegisterMetaType<api::commands::GetMostPopular*>("commands::GetMostPopular*");

	qmlRegisterType<api::GApiAccessData>("api.GApiMethods", 1, 0, "GApiAccessData");
	qmlRegisterType<api::GApiCommandExecutor>("api.GApiMethods", 1, 0, "GApiCommandExecutor");
	qmlRegisterType<api::GApiWrapper>("api.GApiMethods", 1, 0, "GApiWrapper");
	qmlRegisterType<api::UserProfile>("api.GApiMethods", 1, 0, "UserProfile");
	qmlRegisterType<api::commands::GetMostPopular>(
		"api.GApiMethods.Commands", 1, 0, "GetMostPopular");

	QQmlApplicationEngine engine;

	api::GApiAccessData accessData;
	accessData.setAccessKey(api::AccessKey);
	accessData.setAuthUri(QUrl(api::AuthUri));
	accessData.setClientId(api::ClientId);
	accessData.setClientSecret(api::ClientSecret);
	accessData.setRedirectUri(QUrl(api::RedirectUri));
	accessData.setTokenUri(QUrl(api::TokenUri));

	engine.rootContext()->setContextProperty("AccessData", &accessData);

	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
