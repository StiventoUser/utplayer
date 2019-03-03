#include "api/UserProfile.h"

namespace api
{

UserProfile::Type UserProfile::getProfileType() const
{
	return profileType_;
}

void UserProfile::setProfileType(const Type type)
{
	profileType_ = type;
}

}
