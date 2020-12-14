#ifndef FACTORY_H
#define FACTORY_H

#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/UI/Slider.h>
#include <Urho3D/Core/Context.h>

#include <string.h>

#include "Kicker.h"
#include "Detector.h"


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

//#define DEBUG

#ifdef DEBUG
#define DB(X) URHO3D_LOGINFO(String(__FILENAME__) + " " + String(__LINE__))
#else
#define DB(X)
#endif

#include "ConfigFile.h"
#include "ParamLoader.h"

using namespace Urho3D;

enum GameState { MENU, GAME };
enum CameraOrientation { ORTHO_SIDE, CO_FREE, CO_FORWARD, N };

class ConveyorBelt;
class Pusher;

class Factory
{
public:
    Factory(Context* context, Scene* scene, ConfigFile* iniFile);
    ~Factory();
    void LoadParameters(ConfigFile* iniFile);
    void Update(UI* ui, float dt);
    static Vector2 To2D(Vector3 vector3);
    static Vector3 To3D(Vector2 vector2);
    //Vector2 size_;
    ConveyorBelt* conveyorBelts_[4];
    Kicker* kicker_[1];
    Detector* detector_[2];
    static Context* context_;
    static Scene* scene_;
    static ConfigFile* iniFile_;
    static UI* ui_;
protected:
private:
};

#endif // FACTORY_H
