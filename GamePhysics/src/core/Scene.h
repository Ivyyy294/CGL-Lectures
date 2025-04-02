#pragma once

// Interface for a scene that can be shown in the application.
struct Scene {
public:
    // Called when this scene is activated.
    virtual void OnEnable() = 0;
    // Called when this scene is deactivated.
    virtual void OnDisable() = 0;
    // Called every frame to update the scene.
    // deltaTime: Time since the last frame in seconds.
    virtual void Update(float deltaTime) = 0;
    // Called every frame to render the scene.
    virtual void Render() = 0;
    // Returns the display name of the scene.
    virtual const char* GetName() = 0;
};