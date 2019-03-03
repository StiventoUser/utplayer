#pragma once

#include <future>
#include <vector>

#include <QObject>

#include "api/GApiWrapper.h"
#include "api/UserProfile.h"
#include "api/commands/Command.h"

namespace api
{

class GApiCommandExecutor : public QObject
{
	Q_OBJECT

	Q_PROPERTY(
		GApiWrapper* apiWrapper READ getApiWrapper WRITE setApiWrapper NOTIFY apiWrapperChanged)
	Q_PROPERTY(
		UserProfile* userProfile READ getUserProfile WRITE setUserProfile NOTIFY userProfileChanged)

signals:
	void apiWrapperChanged(GApiWrapper*);
	void userProfileChanged(UserProfile*);

public slots:
	GApiWrapper* getApiWrapper() const;
	UserProfile* getUserProfile() const;

	void setApiWrapper(GApiWrapper* wrapper);
	void setUserProfile(UserProfile* profile);

	void execute(commands::Command* command);

private:
	struct Task
	{
		commands::Command* command_;
		std::future<void> fut_;
	};

private:
	GApiWrapper* apiWrapper_ = nullptr;
	std::vector<Task> commandFutures_;
	UserProfile* userProfile_ = nullptr;
};

} // namespace api
