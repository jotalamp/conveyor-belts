#pragma once

#include "Sample.h"

Node* freeCameraNode; // Camera parent Node
Node* cameraTargetNode; // Node to "follow"

Camera* camera;
Text* instructionText = nullptr;

UI* ui;

float cameraSpeed = 0.05f;
float zoomSpeed = 0.02f;
float targetZoom = 2.5f;
float averageDeltaTime = 30.0f;
float cameraYaw     = 0.0f;
float cameraPitch   = 0.0f;

Timer* totalTime;
Timer* boardTimer;

unsigned totalBoards = 0;
float totalMeters = 0.0f;

ResourceCache* cache;

namespace Urho3D
{
    class Node;
    class Scene;
}

class CharacterDemo : public Sample
{
    URHO3D_OBJECT(CharacterDemo, Sample);
public:
    /// Construct.
    explicit CharacterDemo(Context* context);

    /// Destruct.
    ~CharacterDemo() override;

    void Setup() override;

    /// Setup after engine initialization and before running the main loop.
    void Start() override;

    void Stop() override;

private:
    void HandleLoadParametersPressed(StringHash eventType, VariantMap& eventData);
    void HandleSlider1Changed(StringHash eventType, VariantMap& eventData);
    void HandleSlider2Changed(StringHash eventType, VariantMap& eventData);
    void HandleSlider3Changed(StringHash eventType, VariantMap& eventData);
    void HandleSlider4Changed(StringHash eventType, VariantMap& eventData);
    void HandleSceneDrawableUpdateFinished(StringHash /*eventType*/, VariantMap& eventData);
    void HandleASyncLoadFinished(StringHash eventType, VariantMap& eventData);
    void HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData);

    void ResumeGame(StringHash eventType, VariantMap& eventData);
    void ExitGame(StringHash eventType, VariantMap& eventData);
    void HandleNodeCollisionStart(StringHash eventType, VariantMap& eventData);
    void HandleNodeCollision1(StringHash eventType, VariantMap& eventData);
    void HandleNodeCollision2(StringHash eventType, VariantMap& eventData);
    void HandleNodeCollision3 (StringHash eventType, VariantMap& eventData);
    void HandleNodeCollision4(StringHash eventType, VariantMap& eventData);
    void HandlePhysicsCollision(StringHash eventType, VariantMap& eventData);
    void SpawnObject();

    void CreateUI();
    void CreateScene();

    /// Construct an instruction text to the UI.
    void CreateInstructions();
    /// Subscribe to necessary events.
    void SubscribeToEvents();
    void CreateRagdollBone(Node* rootNode, const String& boneName, ShapeType type, const Vector3& size, const Vector3& position,
        const Quaternion& rotation);
    void SpawnObject(int objtype);

    /// Test if some pointers are null
    bool CheckPointers();
    /// Update FPS counter
    void UpdateFPS();
    /// Update time text
    void UpdateTimeText();
    /// If triggers are not subscribed, subscribe them
    void CheckTriggers();
    /// Handle game events
    void HandleGameEvents();
    /// Selecting camera, zooming etc..
    void UpdateCamera();
    /// Handle application update. Set controls to character.
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle application post-update. Update camera position after character has moved.
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Draws vector from startPoint to direction
    void DrawVector( Vector3 startPoint, Vector3 direction, Color color );

    /// First person camera flag.
    bool firstPerson_;

    /// Root UI element of texture.
    //SharedPtr<UIElement> textureRoot_;

    /// The Window.
    //SharedPtr<Window> window_;

    /// The UI's root UIElement.
    //SharedPtr<UIElement> uiRoot_;
};
