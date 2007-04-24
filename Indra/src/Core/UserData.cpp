
#include "Core/UserData.h"

using namespace Core;

cluster::UserData<UserData> UserDataController::mUserData;

vpr::Mutex                  UserDataController::mCommandLock;

