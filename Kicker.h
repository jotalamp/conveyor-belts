#ifndef KICKER_H
#define KICKER_H

#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Sprite.h>
#include <Urho3D/Scene/LogicComponent.h>

#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/IndexBuffer.h>
#include <Urho3D/Graphics/VertexBuffer.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/StaticModel.h>

#include <Urho3D/Graphics/Material.h>

#include <Urho3D/Math/MathDefs.h>

#include "ParamLoader.h"

using namespace Urho3D;

class Factory;

class Kicker : public LogicComponent
{
    URHO3D_OBJECT(Kicker, LogicComponent);
public:
    explicit Kicker(Context* context);
    Kicker(Context* context, Factory* factory, String name);
    ~Kicker();
    static void RegisterObject(Context* context);
    void LoadParameters(ConfigFile* iniFile);
    void Update(float dt);
    void SetSpeed(float speed);

    String name_;
    float speed_;
    Context* context_;
    Vector3 GetPosition();
    Vector2 GetPosition2D();
    Factory* factory_;
    //Node* node_;
    RigidBody* body_;
    SoundSource3D* soundSource_;
    ResourceCache* cache_;

    // Pusher
    int maxBoardsInPacket_ = 10;
    int boardsInPacket_ = 0;
    Timer* timer_;
    bool timerOn_ = false;
    bool pushing_ = false;
    bool goingBack_ = false;
    float pusherLimit_  = -7.4f;
    float pusherMaxLimit_ = -7.4f;
};

#endif // Kicker_H
