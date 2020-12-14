#include "Kicker.h"
#include "Factory.h"
#include "ConveyorBelt.h"

Kicker::Kicker(Context* context) : LogicComponent(context) {}

Kicker::Kicker(Context* context, Factory* factory, String name) : LogicComponent(context)
{
    context_ = context;
    factory_ = factory;
    cache_ = context->GetSubsystem<ResourceCache>();
    name_ = name;
    //node_ = factory_->scene_->GetChild("KickerCylinder01");
    //speed_ = 3.0f;
    timer_ = new Timer();
    LoadParameters(factory_->iniFile_);
}

Kicker::~Kicker()
{
}

void Kicker::RegisterObject(Context* context)
{
    context->RegisterFactory<Kicker>();
}

void Kicker::LoadParameters(ConfigFile* iniFile)
{
    if(iniFile)
    {
        SetSpeed(iniFile->GetFloat(name_, "Speed", 3.0));
    }
}

Vector3 Kicker::GetPosition()
{
    return body_->GetPosition();
}

Vector2 Kicker::GetPosition2D()
{
    return Factory::To2D(GetPosition());
}

void Kicker::SetSpeed(float speed)
{
    speed_ = speed;
}

void Kicker::Update(float dt)
{
    Scene* scene = Factory::scene_;

    Node* pusherNode = scene->GetChild("Pusher", true);
    RigidBody* pusher = pusherNode->GetComponent<RigidBody>();

    float z = pusher->GetPosition().z_;

    float pushingSpeed = 4.0f;

    if( z > -6.64f ) //"home" position
    {
        factory_->conveyorBelts_[3]->SetSpeed(factory_->conveyorBelts_[3]->speed_*0.8f);
        goingBack_ = false;
        pushing_ = false;
        pusher->SetLinearVelocity( Vector3( 0.0f, 0.0f, 0.0f) );
    }

    if( z < pusherLimit_ )
    {
        Vector3 pos = pusher->GetPosition();
        z = pusherLimit_;
        pos.z_ = pusherLimit_;
        pusher->SetPosition(pos);

        if(pushing_)
        {
            pusherLimit_ += 0.048f;
            boardsInPacket_++;
            if(boardsInPacket_ > maxBoardsInPacket_)
            {
                boardsInPacket_ = 0;
                pusherLimit_ = pusherMaxLimit_;
            }
        }
        pushing_ = false;
        goingBack_ = true;
    }
    else if (factory_->detector_[0]->Detect())
    {
        if(!pushing_)
        {
            pushing_ = true;
            goingBack_ = false;
        }

        if(!timerOn_)
        {
            timer_->Reset();
            timerOn_ = true;
        }
    }

    if( (timer_->GetMSec(false) > 50) and pushing_)
    {
        pusher->SetLinearVelocity( Vector3( 0.0f, 0.0f, -3.0f-speed_*1.0f*(pusherLimit_-z)/600.0f));
        timerOn_ = false;
    }

    if(goingBack_)
    {
        pusher->SetLinearVelocity( Vector3( 0.0f, 0.0f, speed_) );

        if(boardsInPacket_ == 0)
        {
            float speed = 3.0f*factory_->conveyorBelts_[3]->speed_+20.0f;
            if(speed>600.0f) speed = 600.0f;
            factory_->conveyorBelts_[3]->SetSpeed(speed);
        }
    }

}
