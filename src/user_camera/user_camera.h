#pragma once

#include <raylib.h>

#define ZOOM_SPEED 0.1f
#define CAMERA_SPEED 800.0f
#define SPRINT_MULTIPLIER 1.8f

#define MIN_ZOOM 0.01f
#define MAX_ZOOM 5.0f

#define ZOOM_LERP_SPEED 8.0f
#define MOVE_LERP_SPEED 10.0f

typedef struct UserCamera {
    Camera2D camera;
    
    float targetZoom;
    Vector2 velocity;
} UserCamera;

UserCamera CreateUserCamera(Vector2 target);
void UpdateUserCamera(UserCamera* userCamera, float deltaTime);
void BeginUserCameraMode(UserCamera* userCamera);
void EndUserCameraMode();

Rectangle GetUserCameraRect(const UserCamera* userCamera);