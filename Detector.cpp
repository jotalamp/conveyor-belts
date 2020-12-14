#include "Detector.h"
#include "Factory.h"
#include "ConveyorBelt.h"

Detector::Detector(Context* context) : LogicComponent(context) {}

Detector::Detector(Context* context, Factory* factory, Node* node) : LogicComponent(context)
{
    context_ = context;
    factory_ = factory;

    UI* ui = context->GetSubsystem<UI>();

    auto* cache = context->GetSubsystem<ResourceCache>();
    cache_ = cache;

    node_ = node;
    //body_ = node_->GetChild


    //if(node_)
        //soundSource_ = node_->CreateComponent<SoundSource3D>();

    //if(soundSource_)
        //soundSource_->SetSoundType(SOUND_EFFECT);  // optional

    //conveyor4Timer = new Timer();
}

Detector::~Detector()
{
}

void Detector::RegisterObject(Context* context)
{
    context->RegisterFactory<Detector>();
}

void Detector::LoadParameters(ConfigFile* iniFile)
{
    if(iniFile)
    {
        //width_       = iniFile->GetInt   (name_, "Width",      200   );
        //length_      = iniFile->GetInt   (name_, "Length",     6000  );
        //radius_      = iniFile->GetInt   (name_, "Radius",     100   );
        //speed_       = iniFile->GetInt   (name_, "Speed",      220   );
        //friction_    = iniFile->GetFloat (name_, "Friction",   0.5   );

        //SetSpeed(iniFile->GetInt   (name_, "Speed",      220   ));
    }
}

void Detector::DrawVector( Vector3 startPoint, Vector3 direction, Color color )
{
    DebugRenderer* dbgRenderer = factory_->scene_->GetComponent<DebugRenderer>();
    if(!dbgRenderer)
        return;
    //direction.Normalize();
    dbgRenderer->AddLine( startPoint, startPoint + direction, color, false );
}

Vector3 Detector::GetPosition()
{
    return node_->GetPosition();
}

Vector2 Detector::GetPosition2D()
{
    return Factory::To2D(GetPosition());
}

bool Detector::Detect()
{
    Scene* scene = Factory::scene_;

    Node* detectorNode = node_;

    PhysicsWorld* phyWorld = scene->GetComponent<PhysicsWorld>();

    Vector3 laserStartPos   = detectorNode->GetPosition() + detectorNode->GetRotation() * Vector3( 0, -0.001f, 0.0f );
    Vector3 laserTargetPos  = detectorNode->GetPosition() + detectorNode->GetRotation() * Vector3( 0, -0.1f  , 0.0f );

    //Vector3 laserStartPos   = detectorNode->GetPosition() + Vector3(0.0f, 0.0f, -0.001f );
    //Vector3 laserTargetPos  = detectorNode->GetPosition() + Vector3(0.0f, 0.0f, -0.1f   );

    DrawVector( laserStartPos, laserTargetPos-laserStartPos, Color(0.0f, 0.0f, 1.0f, 0.1f) );

    PhysicsRaycastResult result1;
    Ray ray1(laserStartPos, laserTargetPos - laserStartPos);
    float l = (laserTargetPos - laserStartPos).Length();
    phyWorld->RaycastSingle(result1, ray1, l);

    if(result1.body_)
        return true;
    else
        return false;
}

void Detector::Update(float dt)
{

}
