#include "camera/camera.h"

#include <math.h>

UserCamera CreateUserCamera(Vector2 target) {
    UserCamera userCamera;

    userCamera.camera.target = target;
    userCamera.camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    userCamera.camera.rotation = 0.0f;
    userCamera.camera.zoom = 1.0f;

    return userCamera;
}

void UpdateUserCamera(UserCamera* userCamera, float deltaTime) {
    userCamera->camera.zoom = expf(
        logf(userCamera->camera.zoom) + ((float)GetMouseWheelMove() * 0.1f)
    );

    if (userCamera->camera.zoom > MAX_ZOOM) userCamera->camera.zoom = MAX_ZOOM;
    else if (userCamera->camera.zoom < MIN_ZOOM) userCamera->camera.zoom = MIN_ZOOM;

    float speed = IsKeyDown(KEY_LEFT_SHIFT) ? CAMERA_SPEED * SPRINT_MULTIPLIER : CAMERA_SPEED;
    speed /= userCamera->camera.zoom;

    if (IsKeyDown(KEY_W)) {
        userCamera->camera.target.y -= speed * deltaTime;
    }
    if (IsKeyDown(KEY_S)) {
        userCamera->camera.target.y += speed * deltaTime;
    }
    if (IsKeyDown(KEY_A)) {
        userCamera->camera.target.x -= speed * deltaTime;
    }
    if (IsKeyDown(KEY_D)) {
        userCamera->camera.target.x += speed * deltaTime;
    }
}

void BeginUserCameraMode(UserCamera *userCamera) {
    BeginMode2D(userCamera->camera);
}

void EndUserCameraMode() {
    EndMode2D();
}