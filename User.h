#ifndef USER_H
#define USER_H

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>

#include "ConfigFile.h"

using namespace Urho3D;

enum UserType { UT_HUMAN_USE_KEYBOARD, UT_HUMAN_USE_JOYSTICK, UT_CPU };

class Player;

class User
{
public:
    User(int ID, ConfigFile* iniFile);
    void LoadParameters(ConfigFile* iniFile);
    bool CheckAndFixJoystick();
    bool ButtonDown();
    int ID_;
    UserType userType_;
    Color color_;
    JoystickState* joystick_;
    Player* player_;
    String arrowMaterialUrl_;
};

#endif // USER_H
