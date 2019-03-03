#pragma once

#include <QObject>

namespace api
{

class UserProfile
	:  public QObject
{
	Q_OBJECT

public:
	enum class Type
	{
		Local,
		Youtube
	};

private:

	Q_ENUM(Type)
	Q_PROPERTY(Type profileType READ getProfileType WRITE setProfileType NOTIFY profileTypeChanged)

signals:
	void profileTypeChanged(Type);

public slots:
	Type getProfileType() const;
	void setProfileType(const Type type);

private:
	Type profileType_;
};

}
