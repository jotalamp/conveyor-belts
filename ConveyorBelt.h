#ifndef CONVEYOR_BELT_H
#define CONVEYOR_BELT_H

#include <Urho3D/Core/Context.h>
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

class ConveyorBelt : public LogicComponent
{
    URHO3D_OBJECT(ConveyorBelt, LogicComponent);
public:
    explicit ConveyorBelt(Context* context);
    ConveyorBelt(Context* context, Factory* factory, Node* node2, String materialName, String name, ConfigFile* iniFile);
    ~ConveyorBelt();
    static void RegisterObject(Context* context);
    void LoadParameters(ConfigFile* iniFile);
    void Update(float dt);
    void SetSpeed(float speed);
    //float speed_;
    String materialName_;
    Context* context_;
    Vector3 GetPosition();
    Vector2 GetPosition2D();

    String name_;
    int width_;
    int length_;
    int radius_;
    float speed_;
    float friction_;
    Vector3 size_;

    Factory* factory_;

    Node* node_;
    Node* nodeCylinders_[2];

    RigidBody* body_;
    RigidBody* bodyCylinders_[2];

    ResourceCache* cache_;
    Sprite* radarSpot_;
};

#endif // ConveyorBelt_H
