#pragma once

#include <mutex>

#include <QObject>

#include "api/ApiRequest.h"
#include "api/ApiResponse.h"

namespace api
{
namespace commands
{

class Command : public QObject
{
	Q_OBJECT

public:
	enum class AccessType
	{
		Public,
		User
	};

signals:
	void commandReadResponse();

public:
	Command(QObject* parent = nullptr);

	virtual AccessType GetAccessType() const = 0;
	virtual ApiRequest GenerateRequest() const = 0;
	virtual void ReadResponse(const ApiResponse& response) = 0;
};

} // namespace commands
} // namespace api
