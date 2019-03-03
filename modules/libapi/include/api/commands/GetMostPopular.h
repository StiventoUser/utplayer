#pragma once

#include "api/commands/Command.h"
#include "api/models/KeyValueModelVectorModel.h"

namespace api
{
namespace commands
{

class GetMostPopular : public Command
{
	Q_OBJECT

public:
	GetMostPopular(QObject* parent = nullptr);

	AccessType GetAccessType() const override;
	ApiRequest GenerateRequest() const override;
	void ReadResponse(const ApiResponse& response) override;

public slots:
	QObject* getModel();
	QObject* getPageModel();

	void resetPaging();

private:
	models::KeyValueModel::ModelType responseData_;
	int itemsPerRequest_ = 20;
	QString nextPageToken_;
};

} // namespace commands
} // namespace api
