#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/BillboardSet.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/UI/ListView.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/ProgressBar.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/Scene/ValueAnimation.h>

#include "CharacterDemo.h"
#include "ConfigFile.h"
#include "ParamLoader.h"
#include "ConveyorBelt.h"
#include "User.h"
#include "Factory.h"

float timeScale = 1.0f;

ConfigFile* iniFile;

Factory* factory;

CharacterDemo::~CharacterDemo() = default;

URHO3D_DEFINE_APPLICATION_MAIN(CharacterDemo)

CharacterDemo::CharacterDemo(Context* context) :
    Sample(context),
    firstPerson_(false)
{
    // Register factory and attributes for the Character component so it can be created via CreateComponent, and loaded / saved
    //Character::RegisterObject(context);
    ConfigFile::RegisterObject(context);
}

CameraOrientation selectedCamera = CameraOrientation::CO_FREE;

void CharacterDemo::HandleSceneDrawableUpdateFinished(StringHash /*eventType*/, VariantMap& eventData)
{
}

void CharacterDemo::Setup()
{
    // fullscreen works if
    // desktop screen resolution 1280x960
    // and engineParameters_["FullScreen"]=true; and
    // engineParameters_["WindowWidth"]=1280; engineParameters_["WindowHeight"]=960;
    //engineParameters_["FullScreen"]=true;
    engineParameters_["FullScreen"]=false;
    engineParameters_["Headless"]= false;
    engineParameters_["WindowWidth"]=1280;
    engineParameters_["WindowHeight"]=960;
    engineParameters_["ResourcePrefixPath"] = "Data2";
}

void CharacterDemo::CreateUI()
{
    auto* graphics = GetSubsystem<Graphics>();
    float width     = (float)(graphics->GetWidth());
    float height    = (float)(graphics->GetHeight());

    auto* cache = GetSubsystem<ResourceCache>();
    cache->SetAutoReloadResources(true);
    ui = GetSubsystem<UI>();

    // Set up global UI style into the root UI element
    auto* style = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    ui->GetRoot()->SetDefaultStyle(style);

    // Create a Cursor UI element because we want to be able to hide and show it at will. When hidden, the mouse cursor will
    // control the camera, and when visible, it will interact with the UI
    SharedPtr<Cursor> cursor(new Cursor(context_));
    cursor->SetStyleAuto();
    ui->SetCursor(cursor);

    // Load UI content prepared in the editor and add to the UI hierarchy
    SharedPtr<UIElement> layoutRoot = ui->LoadLayout(cache->GetResource<XMLFile>("UI/ConveyorUI04.xml"));
    ui->GetRoot()->AddChild(layoutRoot);

    ui->SetFocusElement(nullptr,true);

    auto buttonLoadParameters = (Button*) ui->GetRoot()->GetChild("LoadParameters",true);
    SubscribeToEvent(buttonLoadParameters, E_RELEASED, URHO3D_HANDLER(CharacterDemo, HandleLoadParametersPressed));

    auto slider1 = (Slider*) ui->GetRoot()->GetChild("ConveyorSpeed01",true);
    SubscribeToEvent(slider1, E_SLIDERCHANGED, URHO3D_HANDLER(CharacterDemo, HandleSlider1Changed));
    slider1->SetValue(factory->conveyorBelts_[0]->speed_);

    auto slider2 = (Slider*) ui->GetRoot()->GetChild("ConveyorSpeed02",true);
    SubscribeToEvent(slider2, E_SLIDERCHANGED, URHO3D_HANDLER(CharacterDemo, HandleSlider2Changed));
    slider2->SetValue(factory->conveyorBelts_[1]->speed_);

    auto slider3 = (Slider*) ui->GetRoot()->GetChild("ConveyorSpeed03",true);
    SubscribeToEvent(slider3, E_SLIDERCHANGED, URHO3D_HANDLER(CharacterDemo, HandleSlider3Changed));
    slider3->SetValue(factory->conveyorBelts_[2]->speed_);

    auto slider4 = (Slider*) ui->GetRoot()->GetChild("ConveyorSpeed04",true);
    SubscribeToEvent(slider4, E_SLIDERCHANGED, URHO3D_HANDLER(CharacterDemo, HandleSlider4Changed));
    slider4->SetValue(factory->conveyorBelts_[3]->speed_);

    auto slider5 = (Slider*) ui->GetRoot()->GetChild("SawSpeed",true);
    //SubscribeToEvent(slider5, E_SLIDERCHANGED, URHO3D_HANDLER(CharacterDemo, HandleSlider1Changed));

    int sawSpeed = 700;
    if(iniFile)
        sawSpeed = iniFile->GetInt("Saw", "Speed", 700);
    slider5->SetValue(sawSpeed);

    Factory::ui_ = ui;
}

void CharacterDemo::HandleLoadParametersPressed(StringHash eventType, VariantMap& eventData)
{
    iniFile = cache->GetResource<ConfigFile>("ConveyorBelts.ini");
    factory->LoadParameters(iniFile);
    auto slider    = (Slider*) ui->GetRoot()->GetChild("ConveyorSpeed02"       ,true);
    if(slider)
        slider->SetValue(factory->conveyorBelts_[1]->speed_);
}

void CharacterDemo::HandleSlider1Changed(StringHash eventType, VariantMap& eventData)
{
    auto text      = (Text*)   ui->GetRoot()->GetChild("ConveyorSpeed01Text"   ,true);
    int speed = eventData[SliderChanged::P_VALUE].GetFloat();
    text->SetText((String)speed);
    factory->conveyorBelts_[0]->SetSpeed(speed);
}

void CharacterDemo::HandleSlider2Changed(StringHash eventType, VariantMap& eventData)
{
    auto text      = (Text*)   ui->GetRoot()->GetChild("ConveyorSpeed02Text"   ,true);
    int speed = eventData[SliderChanged::P_VALUE].GetFloat();
    text->SetText((String)speed);
    factory->conveyorBelts_[1]->SetSpeed(speed);
}

void CharacterDemo::HandleSlider3Changed(StringHash eventType, VariantMap& eventData)
{
    auto text      = (Text*)   ui->GetRoot()->GetChild("ConveyorSpeed03Text"   ,true);
    int speed = eventData[SliderChanged::P_VALUE].GetFloat();
    text->SetText((String)speed);
    factory->conveyorBelts_[2]->SetSpeed(speed);
}

void CharacterDemo::HandleSlider4Changed(StringHash eventType, VariantMap& eventData)
{
    auto text      = (Text*)   ui->GetRoot()->GetChild("ConveyorSpeed04Text"   ,true);
    int speed = eventData[SliderChanged::P_VALUE].GetFloat();
    text->SetText((String)speed);
    factory->conveyorBelts_[3]->SetSpeed(speed);
}

void CharacterDemo::Start()
{
    // Execute base class startup
    Sample::Start();
    CreateScene();// Create static scene content
    CreateUI();// Create the UI content
    SubscribeToEvents();// Subscribe to necessary events
    CreateInstructions();// Create the UI content
}

void CharacterDemo::SubscribeToEvents()
{
    // Subscribe to Update event for setting the character controls before physics simulation
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(CharacterDemo, HandleUpdate));

    // Subscribe to PostUpdate event for updating the camera position after physics simulation
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(CharacterDemo, HandlePostUpdate));

    SubscribeToEvent(E_ASYNCLOADFINISHED, URHO3D_HANDLER(CharacterDemo, HandleASyncLoadFinished));

    // Subscribe HandlePostRenderUpdate() function for processing the post-render update event, during which we request
    // debug geometry
    SubscribeToEvent(E_POSTRENDERUPDATE, URHO3D_HANDLER(CharacterDemo, HandlePostRenderUpdate));
}

void CharacterDemo::Stop()
{
}

void CharacterDemo::ResumeGame(StringHash eventType, VariantMap& eventData)
{
    ui->SetFocusElement(nullptr,false);
    scene_->SetUpdateEnabled(true);
}

void CharacterDemo::ExitGame(StringHash eventType, VariantMap& eventData)
{
    engine_->Exit();
}

void CharacterDemo::CreateScene()
{

    SetRandomSeed(Time::GetSystemTime());

    cache = GetSubsystem<ResourceCache>();

    iniFile = cache->GetResource<ConfigFile>("ConveyorBelts.ini");
    Prm.LoadValuesFromIni(iniFile);

    scene_ = new Scene(context_);

    scene_->LoadXML(*cache->GetFile("Scenes/ConveyorBelts/ConveyorBelts20.xml"));
    scene_->CreateComponent<DebugRenderer>();

    scene_->SetTimeScale(timeScale);

    // Create camera and define viewport. We will be doing load / save, so it's convenient to create the camera outside the scene,
    // so that it won't be destroyed and recreated, and we don't have to redefine the viewport on load
    Node* freeCameraMover = scene_->GetChild("FreeCameraMover");

    Node* mouseNode = scene_->CreateChild("MouseNode");

    Node* cameraRotateNode_ = scene_->CreateChild("CameraRotate");
    cameraNode_ = cameraRotateNode_->CreateChild("Camera");
    camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(150.0f);

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(30, 0, -4));
    cameraRotateNode_->SetPosition(Vector3(30, 0, -3));

    freeCameraNode = cameraRotateNode_;

    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    GetSubsystem<Renderer>()->SetViewport(0, viewport);

    // bloom and FXAA post process effects to the front viewport. Render path commands can be tagged
    // for example with the effect name to allow easy toggling on and off. We start with the effects
    // disabled.
    RenderPath* effectRenderPath=viewport->GetRenderPath();

    auto* cache = GetSubsystem<ResourceCache>();

    // for 3D sounds to work
    SoundListener* listener=cameraNode_->CreateComponent<SoundListener>();
    GetSubsystem<Audio>()->SetListener(listener);

    // you can set master volumes for the different kinds if sounds
    GetSubsystem<Audio>()->SetMasterGain(SOUND_MUSIC,0.9);
    GetSubsystem<Audio>()->SetMasterGain(SOUND_EFFECT,1.0);

    totalTime = new Timer();

    Factory::scene_ = scene_;
    Factory::iniFile_ = iniFile;
    Factory::context_ = context_;

    using namespace Update;

    auto* input = GetSubsystem<Input>();

    factory = new Factory(context_, scene_, iniFile);

    boardTimer = new Timer();

    URHO3D_LOGINFO("[Scene created]");
}

void CharacterDemo::CreateInstructions()
{
    auto* cache = GetSubsystem<ResourceCache>();
    DB();

    // Construct new Text object, set string to display and font to use
    instructionText = ui->GetRoot()->CreateChild<Text>();
    instructionText->SetName("InstructionText");
    instructionText->SetColor(Color(0.9f,0.9f,0.9f,0.9f));
    instructionText->SetText("testi");

    instructionText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 8);
    // The text has multiple rows. Center them in relation to each other
    instructionText->SetTextAlignment(HA_CENTER);

    // Position the text relative to the screen center
    instructionText->SetHorizontalAlignment(HA_RIGHT);
    instructionText->SetVerticalAlignment(VA_TOP);
    DB();
    instructionText->SetPosition(0, 0);
}

void CharacterDemo::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{
}

void CharacterDemo::HandleASyncLoadFinished(StringHash eventType, VariantMap& eventData)
{
    //Node* cylinder01Node = scene_->CreateChild("Cylinder01Node");
    //cylinder01Node = scene_->GetChild("ConveyorBeltCylinder01", true);
}

void CharacterDemo::SpawnObject()
{
    auto* cache = GetSubsystem<ResourceCache>();

    Node* boxNode = scene_->CreateChild("Board");

    //Vector3 boardSize = Vector3( 0.001f * Random(180, 500), 0.0275f, 0.097f );
    Vector3 boardSize = Vector3( 0.001f * Random(250, 300), 0.048f, 0.048f );

    //boxNode->SetPosition(Vector3(0.0f,0.8f + 1.1f*boardSize.y_,0.0f));

    Node* spawnObject = scene_->GetChild("SpawnObject", true);
    if(spawnObject)
        boxNode->SetPosition(spawnObject->GetPosition());

    boxNode->SetScale( boardSize );
    auto* boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/Wood.xml"));
    boxObject->SetCastShadows(true);

    // Create physics components, use a smaller mass also
    auto* body = boxNode->CreateComponent<RigidBody>();
    body->SetMass( boardSize.x_ * boardSize.y_ * boardSize.z_ * 500.0f );
    body->SetFriction(0.6f);
    body->SetAngularDamping(0.8f);
    body->SetCcdRadius(0.06f);
    body->SetCcdMotionThreshold(2);
    auto* shape = boxNode->CreateComponent<CollisionShape>();
    shape->SetBox(Vector3::ONE);
}

void CharacterDemo::HandleNodeCollisionStart(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;
    Node* contact_node = (Node*)eventData[P_OTHERNODE].GetPtr();
    VectorBuffer contacts = eventData[P_CONTACTS].GetBuffer();
    Vector3 pos = contacts.ReadVector3();

    RigidBody* contact_body = (RigidBody*)eventData[P_OTHERBODY].GetPtr();

    if(contact_node and ( contact_node->GetName()=="Board") )
    {
        totalBoards++;

        auto piecesPerMinute = (Text*)ui->GetRoot()->GetChild("PiecesPerMinute",true);
        piecesPerMinute->SetText(String(1000*60*totalBoards/(totalTime->GetMSec(false)))+" kpl/min");

        auto homeGoals = (Text*)ui->GetRoot()->GetChild("homeGoals",true);
        homeGoals->SetText(String(totalBoards));

        totalMeters += contact_node->GetScale().x_;

        auto awayGoals = (Text*)ui->GetRoot()->GetChild("awayGoals",true);

        float value = (int)(totalMeters * 10 + .5);
        //float value = 100.0f;
        float roundedMeters = (float)value / 10;

        awayGoals->SetText(String(roundedMeters));
        //awayGoals->SetText("TESTI");

        auto metersPerHour = (Text*)ui->GetRoot()->GetChild("MetersPerHour",true);
        metersPerHour->SetText(String(1000*60*60*totalMeters/(totalTime->GetMSec(false))));

        contact_node->Remove();
    }
}

void CharacterDemo::HandleNodeCollision1(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;

    float frictionFactor = 0.5f;

    Node* contact_node = (Node*)eventData[P_OTHERNODE].GetPtr();
    VectorBuffer contacts = eventData[P_CONTACTS].GetBuffer();
    Vector3 pos = contacts.ReadVector3();

    RigidBody* contact_body  = (RigidBody*)eventData[P_OTHERBODY].GetPtr();
    RigidBody* contact_body1 = (RigidBody*)eventData[P_BODY].GetPtr();

    /// Conveyor Belt!
    if(contact_node)
    {
        //int id = contact_node->GetID();
        String name = contact_node->GetName();

        float speed = factory->conveyorBelts_[0]->speed_/60.0f;

        if(contact_body)
        {
            Vector3 v1 = contact_body->GetLinearVelocity();
            Vector3 v2;

            v2 = contact_body1->GetRotation() * Vector3(0,0,speed);

            //v2.z_ *= 0.6f; // slowing z-axis conveyors

            Vector3 v3 = v2 - v1;

            contact_body->SetLinearVelocity( v1 + frictionFactor * v3 );
        }
    }

}

void CharacterDemo::HandleNodeCollision2(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;

    float frictionFactor = 0.5f;

    Node* contact_node = (Node*)eventData[P_OTHERNODE].GetPtr();
    VectorBuffer contacts = eventData[P_CONTACTS].GetBuffer();
    Vector3 pos = contacts.ReadVector3();

    RigidBody* contact_body  = (RigidBody*)eventData[P_OTHERBODY].GetPtr();
    RigidBody* contact_body1 = (RigidBody*)eventData[P_BODY].GetPtr();

    /// Conveyor Belt!
    if(contact_node)
    {
        //int id = contact_node->GetID();
        String name = contact_node->GetName();

        float speed = factory->conveyorBelts_[1]->speed_/60.0f;

        if(contact_body)
        {
            Vector3 v1 = contact_body->GetLinearVelocity();
            Vector3 v2;

            v2 = contact_body1->GetRotation() * Vector3(0,0,speed);

            //v2.z_ *= 0.6f; // slowing z-axis conveyors

            Vector3 v3 = v2 - v1;

            contact_body->SetLinearVelocity( v1 + frictionFactor * v3 );
        }
    }

}

void CharacterDemo::HandleNodeCollision3(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;

    float frictionFactor = 0.5f;

    Node* contact_node = (Node*)eventData[P_OTHERNODE].GetPtr();
    VectorBuffer contacts = eventData[P_CONTACTS].GetBuffer();
    Vector3 pos = contacts.ReadVector3();

    RigidBody* contact_body  = (RigidBody*)eventData[P_OTHERBODY].GetPtr();
    RigidBody* contact_body1 = (RigidBody*)eventData[P_BODY].GetPtr();

    /// Conveyor Belt!
    if(contact_node)
    {
        //int id = contact_node->GetID();
        String name = contact_node->GetName();

        float speed = factory->conveyorBelts_[2]->speed_/60.0f;

        if(contact_body)
        {
            Vector3 v1 = contact_body->GetLinearVelocity();
            Vector3 v2;

            v2 = contact_body1->GetRotation() * Vector3(0,0,speed);

            //v2.z_ *= 0.6f; // slowing z-axis conveyors

            Vector3 v3 = v2 - v1;

            contact_body->SetLinearVelocity( v1 + frictionFactor * v3 );
        }
    }

}

void CharacterDemo::HandleNodeCollision4(StringHash eventType, VariantMap& eventData)
{
    using namespace NodeCollision;

    float frictionFactor = 0.5f;

    Node* contact_node = (Node*)eventData[P_OTHERNODE].GetPtr();
    VectorBuffer contacts = eventData[P_CONTACTS].GetBuffer();
    Vector3 pos = contacts.ReadVector3();

    RigidBody* contact_body  = (RigidBody*)eventData[P_OTHERBODY].GetPtr();
    RigidBody* contact_body1 = (RigidBody*)eventData[P_BODY].GetPtr();

    /// Conveyor Belt!
    if(contact_node)
    {
        //int id = contact_node->GetID();
        String name = contact_node->GetName();

        float speed = factory->conveyorBelts_[3]->speed_/60.0f;

        if(contact_body)
        {
            Vector3 v1 = contact_body->GetLinearVelocity();
            Vector3 v2;

            v2 = contact_body1->GetRotation() * Vector3(0,0,speed);

            //v2.z_ *= 0.6f; // slowing z-axis conveyors

            Vector3 v3 = v2 - v1;

            contact_body->SetLinearVelocity( v1 + frictionFactor * v3 );
        }
    }

}

void CharacterDemo::HandlePhysicsCollision(StringHash eventType, VariantMap& eventData)
{
}

void CharacterDemo::DrawVector( Vector3 startPoint, Vector3 direction, Color color )
{
    DebugRenderer* dbgRenderer = scene_->GetComponent<DebugRenderer>();
    if(!dbgRenderer)
        return;
    //direction.Normalize();
    dbgRenderer->AddLine( startPoint, startPoint + direction, color, false );
}

bool CharacterDemo::CheckPointers()
{
    return true;
}

void CharacterDemo::UpdateFPS()
{
    float smoothDeltaTime = GetSubsystem<Engine>()->GetNextTimeStep();
    averageDeltaTime = 0.05f*smoothDeltaTime + 0.95f*averageDeltaTime;
    auto textFPS = (Text*)ui->GetRoot()->GetChild("FPSCounter",true);
    if (textFPS and averageDeltaTime>0.0f)
        textFPS->SetText("FPS: "+String((int)(1.0f/averageDeltaTime)));
}

void CharacterDemo::UpdateTimeText()
{
    auto textTime = (Text*)ui->GetRoot()->GetChild("time",true);
    unsigned seconds = totalTime->GetMSec(false)/1000;
    unsigned minutes = seconds/60;
    seconds = seconds % 60;
    if(seconds<10)
        textTime->SetText(String(minutes)+":0"+String(seconds));
    else
        textTime->SetText(String(minutes)+":"+String(seconds));
}

void CharacterDemo::CheckTriggers()
{
    /// Conveyor belt
    Node* conveyorBeltTriggerNode = scene_->GetChild("ConveyorBelt1", true);

    if(conveyorBeltTriggerNode)
    {
        SubscribeToEvent(conveyorBeltTriggerNode, E_NODECOLLISION, URHO3D_HANDLER(CharacterDemo, HandleNodeCollision1));
    }

    /// Conveyor belt 2
    Node* conveyorBeltTriggerNode2 = scene_->GetChild("ConveyorBelt2", true);

    if(conveyorBeltTriggerNode2)
    {
        SubscribeToEvent(conveyorBeltTriggerNode2, E_NODECOLLISION, URHO3D_HANDLER(CharacterDemo, HandleNodeCollision2));
    }

    /// Conveyor belt 3
    Node* conveyorBeltTriggerNode3 = scene_->GetChild("ConveyorBelt3", true);

    if(conveyorBeltTriggerNode3)
    {
        SubscribeToEvent(conveyorBeltTriggerNode3, E_NODECOLLISION, URHO3D_HANDLER(CharacterDemo, HandleNodeCollision3));
    }

    /// Conveyor belt 4
    Node* conveyorBeltTriggerNode4 = scene_->GetChild("ConveyorBelt4", true);

    if(conveyorBeltTriggerNode4)
    {
        SubscribeToEvent(conveyorBeltTriggerNode4, E_NODECOLLISION, URHO3D_HANDLER(CharacterDemo, HandleNodeCollision4));
    }

    /// Remove volume
    Node* removeTriggerNode = scene_->GetChild("Remove", true);

    if(removeTriggerNode)
    {
        SubscribeToEvent(removeTriggerNode, E_NODECOLLISIONSTART, URHO3D_HANDLER(CharacterDemo, HandleNodeCollisionStart));
    }
}

void CharacterDemo::HandleGameEvents()
{
}

void CharacterDemo::UpdateCamera()
{
    auto* input = GetSubsystem<Input>();

    Node* freeCameraMover = scene_->GetChild("FreeCameraMover");

    targetZoom +=  input->GetMouseMoveWheel();//Clamp(camera->GetZoom() * (1.0f - 2.0f * input->), 1.0f, 50.0f);
    targetZoom = Clamp( targetZoom, 0.8f, 9.0f );

    float speed = 0.05f;
    if( input->GetKeyDown(KEY_W) or input->GetKeyDown(KEY_UP    ) ) freeCameraMover->SetPosition( freeCameraMover->GetPosition() + Vector3( speed, 0.0f,  0.0) );
    if( input->GetKeyDown(KEY_S) or input->GetKeyDown(KEY_DOWN  ) ) freeCameraMover->SetPosition( freeCameraMover->GetPosition() + Vector3(-speed, 0.0f,  0.0) );
    if( input->GetKeyDown(KEY_A) or input->GetKeyDown(KEY_LEFT  ) ) freeCameraMover->SetPosition( freeCameraMover->GetPosition() + Vector3( 0.0f, 0.0f,  speed) );
    if( input->GetKeyDown(KEY_D) or input->GetKeyDown(KEY_RIGHT ) ) freeCameraMover->SetPosition( freeCameraMover->GetPosition() + Vector3( 0.0f, 0.0f, -speed) );

    if( input->GetKeyPress(KEY_1    ) ) selectedCamera = CameraOrientation::CO_FREE;

    if (input->GetKeyPress(KEY_Y)) selectedCamera = static_cast<CameraOrientation>((selectedCamera + 1) % CameraOrientation::N);

    if(cameraTargetNode) freeCameraNode->SetPosition(0.96f * freeCameraNode->GetPosition() + 0.04f * cameraTargetNode->GetPosition());

    camera->SetZoom((1.0f-zoomSpeed)*camera->GetZoom()+zoomSpeed*targetZoom);

    auto textCamera = (Text*)ui->GetRoot()->GetChild("TextCamera",true);

    switch(selectedCamera)
    {
    case CameraOrientation::ORTHO_SIDE :
    {
        textCamera->SetText("Orthogonal Side");
        //freeCameraNode->SetRotation(Quaternion(0, 0, 0));
        Vector3 oldPos = freeCameraNode->GetPosition();
        freeCameraNode->SetPosition(Vector3(oldPos.x_,oldPos.y_+0.1f,oldPos.z_));
        Graphics* graphics = context_->GetSubsystem<Graphics>();
        camera->SetOrthographic(true); // Set camera orthographic
        camera->SetOrthoSize((float)graphics->GetHeight()*0.02f); // Set camera ortho size (the value of PIXEL_SIZE is 0.01)
        Vector3 lookAtPosition = freeCameraNode->GetPosition();
        cameraYaw = 0.0f;
        cameraPitch = 0.01f;
        Vector3 cameraOffset(0.0f, 0.0f, -10.0f);  // Camera offset relative to target node
        cameraNode_->SetPosition(cameraOffset);  // Set new camera position and lookat values
        freeCameraNode->SetRotation(Quaternion(cameraPitch, cameraYaw, 0.0f));
        cameraNode_->LookAt( lookAtPosition, Vector3::UP );
        break;
    }
    case CameraOrientation::CO_FREE :
    {
        //targetZoom = 10.0f;
        textCamera->SetText("Free");
        //if(!cameraTargetNode) cameraTargetNode = factory->ball_->node_;
        //if(!cameraTargetNode)
        cameraTargetNode = freeCameraMover;//factory->ball_->node_;
        camera->SetOrthographic(false);
        Vector3 lookAtPosition = freeCameraNode->GetPosition();

        if(input->GetMouseButtonDown(MOUSEB_RIGHT))
        {
            cameraYaw   -= 0.5f * (float)input->GetMouseMoveX();
            cameraPitch -= 0.5f * (float)input->GetMouseMoveY();
        }

        cameraPitch  = Clamp(cameraPitch, 0.1f, 89.9f);

        Vector3 cameraOffset(0.0f, 0.1f, -10.0f);  // Camera offset relative to target node

        cameraNode_->SetPosition(cameraOffset);  // Set new camera position and lookat values
        freeCameraNode->SetRotation(Quaternion(cameraPitch, cameraYaw, 0.0f));
        cameraNode_->LookAt( lookAtPosition + (Vector3(0,1,0)), Vector3::UP );
        break;
    }
    case CameraOrientation::CO_FORWARD :
    {
        textCamera->SetText("Forward");
        //freeCameraNode->SetRotation(Quaternion(0, 0, 0));
        Vector3 oldPos = freeCameraNode->GetPosition();
        freeCameraNode->SetPosition(Vector3(oldPos.x_,oldPos.y_+0.05f,oldPos.z_));
        Graphics* graphics = context_->GetSubsystem<Graphics>();
        camera->SetOrthographic(false); // Set camera orthographic
        Vector3 lookAtPosition = freeCameraNode->GetPosition();
        cameraYaw = 90.0f;
        cameraPitch = 0.0f;
        Vector3 cameraOffset(0.0f, 0.0f, -10.0f);  // Camera offset relative to target node
        cameraNode_->SetPosition(cameraOffset);  // Set new camera position and lookat values
        freeCameraNode->SetRotation(Quaternion(cameraPitch, cameraYaw, 0.0f));
        cameraNode_->LookAt( lookAtPosition, Vector3::UP );
        break;
    }
    default :
    {
        textCamera->SetText("----");
        break;
    }
    }

}

void CharacterDemo::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    // Take the frame time step, which is stored as a float
    float dt = eventData[Update::P_TIMESTEP].GetFloat();

    UpdateFPS();

    UpdateTimeText();

    CheckTriggers();

    HandleGameEvents();

    auto textTimer = (Text*)ui->GetRoot()->GetChild("Timer01",true);
    if(textTimer)
    {
        int timerValue = factory->kicker_[0]->timer_->GetMSec(false);
        textTimer->SetText((String)timerValue);
    }

    auto text = (Text*)ui->GetRoot()->GetChild("SawSpeed3",true);
    auto slider = (Slider*)ui->GetRoot()->GetChild("SawSpeed",true);
    int sawSpeed = slider->GetValue();
    text->SetText((String)sawSpeed);

    if( boardTimer->GetMSec(false) > Random(sawSpeed,1900) )
    {
        SpawnObject();
        boardTimer = new Timer();
    }

    factory->Update(ui, dt);

    auto* input = GetSubsystem<Input>();

    DebugRenderer* dbgRenderer = scene_->GetComponent<DebugRenderer>();

    Graphics* graphics = context_->GetSubsystem<Graphics>();
    float width = (float)(graphics->GetWidth());
    float height = (float)(graphics->GetHeight());

    if(input->GetMouseButtonDown(MOUSEB_RIGHT))
    {
        ui->GetRoot()->SetOpacity(1.0f);
        auto* button = ui->GetRoot()->GetChildStaticCast<Button>("ResumeGame", true);
        if(button)
        {
            button->SetSelected(true);
            IntVector2 pos = button->GetScreenPosition();
            input->SetMousePosition(pos);
        }
    }

    if (input->GetKeyPress(KEY_0))
    {
        SpawnObject();
    }

}

void CharacterDemo::HandlePostUpdate(StringHash eventType, VariantMap& eventData)
{
    UpdateCamera();
}
