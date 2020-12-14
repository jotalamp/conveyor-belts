#include "User.h"
//#include "Player.h"
//#include "Controller.h"

User::User(int ID, ConfigFile* iniFile)
{
    ID_ = ID;
    LoadParameters(iniFile);
}

bool User::ButtonDown()
{
}

void User::LoadParameters(ConfigFile* iniFile)
{
    //if(!iniFile) return;
    String section = "User" + String(ID_);
    color_              = iniFile->GetColor (section, "Color", Color(1,1,1,1));
    arrowMaterialUrl_   = iniFile->GetString(section, "Material", "Materials/ArrowRed.xml");
}

bool User::CheckAndFixJoystick()
{
    switch(userType_)
    {

    case UserType::UT_CPU :
    {
        joystick_ = nullptr;
        break;
    }
    case UserType::UT_HUMAN_USE_JOYSTICK :
    {
        break;
    }
    case UserType::UT_HUMAN_USE_KEYBOARD :
    {
        joystick_ = nullptr;
        break;
    }

    }
}
