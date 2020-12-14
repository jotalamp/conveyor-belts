#ifndef DETECTOR_H
#define DETECTOR_H

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

#include <Urho3D/Graphics/DebugRenderer.h>

#include <Urho3D/Physics/PhysicsWorld.h>

#include <Urho3D/Math/Ray.h>

#include "ParamLoader.h"

using namespace Urho3D;

class Factory;

class Detector : public LogicComponent
{
    URHO3D_OBJECT(Detector, LogicComponent);
public:
    explicit Detector(Context* context);
    Detector(Context* context, Factory* factory, Node* node);
    ~Detector();
    static void RegisterObject(Context* context);
    void LoadParameters(ConfigFile* iniFile);
    void DrawVector( Vector3 startPoint, Vector3 direction, Color color );
    bool Detect();
    void Update(float dt);
    //void SetSpeed(float speed);

    String name_;
    //float speed_;
    Context* context_;
    Vector3 GetPosition();
    Vector2 GetPosition2D();
    Factory* factory_;
    Node* node_;
    //RigidBody* body_;
    SoundSource3D* soundSource_;
    ResourceCache* cache_;
};

#endif // Detector_H
