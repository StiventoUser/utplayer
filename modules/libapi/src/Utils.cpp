#include <QCoreApplication>
#include <QMetaObject>
#include <QThread>

#include "api/Utils.h"

namespace api
{
namespace utils
{

void ExecuteOnMainThread(const std::function<void(void)> func, const bool isSync)
{
	const auto isMainThread = IsMainThread();

	if (isMainThread)
	{
		func();
	}
	else
	{
		QMetaObject::invokeMethod(
			QCoreApplication::instance(),
			func,
			isSync ? Qt::BlockingQueuedConnection : Qt::QueuedConnection);
	}
}

bool IsMainThread()
{
	return QCoreApplication::instance()->thread() == QThread::currentThread();
}

utility::string_t QStringToStringT(const QString& str)
{
#ifdef _UTF16_STRINGS
	return str.toStdWString();
#else
	return str.toStdString();
#endif
}

QString StringTToQString(const utility::string_t& str)
{
#ifdef _UTF16_STRINGS
	return QString::fromStdWString(str);
#else
	return QString::fromStdString(str);
#endif
}

} // namespace utils
} // namespace api
