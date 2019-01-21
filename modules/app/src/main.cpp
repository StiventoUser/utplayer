#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "ApiConfig.h"
#include "api/YtWrapper.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	QQuickStyle::setStyle("Universal");

	qmlRegisterType<api::YtWrapper>("api.YtMethods", 1, 0, "YtWrapper");

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("ClientId", QVariant::fromValue<QString>(api::ClientId));
	engine.rootContext()->setContextProperty("ClientSecret", QVariant::fromValue<QString>(api::ClientSecret));
	engine.rootContext()->setContextProperty("AuthUri", QVariant::fromValue<QString>(api::AuthUri));
	engine.rootContext()->setContextProperty("RedirectUri", QVariant::fromValue<QString>(api::RedirectUri));
	engine.rootContext()->setContextProperty("TokenUri", QVariant::fromValue<QString>(api::TokenUri));

	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
