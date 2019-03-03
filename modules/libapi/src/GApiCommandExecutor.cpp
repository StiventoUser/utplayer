#include <QDebug>

#include "api/GApiCommandExecutor.h"
#include "api/Utils.h"

namespace api
{

GApiWrapper* GApiCommandExecutor::getApiWrapper() const
{
	return apiWrapper_;
}

UserProfile* GApiCommandExecutor::getUserProfile() const
{
	return userProfile_;
}

void GApiCommandExecutor::setApiWrapper(GApiWrapper* wrapper)
{
	apiWrapper_ = wrapper;
}

void GApiCommandExecutor::setUserProfile(UserProfile* profile)
{
	userProfile_ = profile;
}

void GApiCommandExecutor::execute(commands::Command* command)
{
	commandFutures_.erase(
		std::remove_if(
			commandFutures_.begin(),
			commandFutures_.end(),
			[](const auto& task) {
				return task.fut_.wait_for(std::chrono::milliseconds(0))
					== std::future_status::ready;
			}),
		commandFutures_.end());

	if (std::find_if(
			commandFutures_.begin(),
			commandFutures_.end(),
			[command](const auto& task) { return task.command_ == command; })
		!= commandFutures_.end())
	{
		qWarning() << "The same command was sent on execution twice";
		return;
	}

	switch (command->GetAccessType())
	{
	case commands::Command::AccessType::Public:
	{
		const auto requestProcessor = [this, command]() {
			auto req = command->GenerateRequest();
			auto resp = apiWrapper_->requestPublicData(req);

			utils::ExecuteOnMainThread(
				[command, resp = std::move(resp)]() { command->ReadResponse(resp); }, false);
		};

		commandFutures_.push_back({command, std::async(std::launch::async, requestProcessor)});
		break;
	}
	default:
		qWarning() << "Unknown command access type: " << static_cast<int>(command->GetAccessType());
		break;
	}
}

} // namespace api
