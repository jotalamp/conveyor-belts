#include "Factory.h"
#include "ConveyorBelt.h"

Factory::Factory(Context* context, Scene* scene, ConfigFile* iniFile)
{
    context_ = context;
    iniFile_ = iniFile;

    Node* nodes[4];
    nodes[0] = scene_->GetChild("ConveyorBelt1");
    nodes[1] = scene_->GetChild("ConveyorBelt2");
    nodes[2] = scene_->GetChild("ConveyorBelt3");
    nodes[3] = scene_->GetChild("ConveyorBelt4");

    conveyorBelts_[0] = new ConveyorBelt(context, this, nodes[0], "Data2/Materials/ConveyorBelt01.xml", "ConveyorBelt01", iniFile_);
    conveyorBelts_[1] = new ConveyorBelt(context, this, nodes[1], "Data2/Materials/ConveyorBelt02.xml", "ConveyorBelt02", iniFile_);
    conveyorBelts_[2] = new ConveyorBelt(context, this, nodes[2], "Data2/Materials/ConveyorBelt03.xml", "ConveyorBelt03", iniFile_);
    conveyorBelts_[3] = new ConveyorBelt(context, this, nodes[3], "Data2/Materials/ConveyorBelt04.xml", "ConveyorBelt04", iniFile_);

    kicker_[0] = new Kicker(context, this, "Kicker01");
    detector_[0] = new Detector(context, this, this->scene_->GetChild("Detector01"));
    detector_[1] = new Detector(context, this, this->scene_->GetChild("Detector02"));

    if(ui_)
    {
        auto slider = (Slider*)ui_->GetRoot()->GetChild("ConveyorSpeed01",true);
        slider->SetValue(conveyorBelts_[0]->speed_);
    }
}

Factory::~Factory()
{
}

void Factory::LoadParameters(ConfigFile* iniFile)
{
    if(iniFile)
        for(int i=0;i<4;i++)
            conveyorBelts_[i]->LoadParameters(iniFile);
}

Vector2 Factory::To2D(Vector3 vector3)
{
    return Vector2(vector3.x_, vector3.z_);
}

Vector3 Factory::To3D(Vector2 vector2)
{
    return Vector3(vector2.x_, 0.0f, vector2.y_);
}

void Factory::Update(UI* ui, float dt)
{
    detector_[0]->Update(dt);
    detector_[1]->Update(dt);
    kicker_[0]->Update(dt);

    for(int i=0;i<4;i++)
        conveyorBelts_[i]->Update(dt);
}

Scene* Factory::scene_;
ConfigFile* Factory::iniFile_;
Context* Factory::context_ = nullptr;
UI* Factory::ui_ = nullptr;
