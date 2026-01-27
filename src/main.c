#include <raylib.h>
#include <time.h>
#include "camera/camera.h"
#include "entity/entity.h"
#include "entity_manager/entity_manager.h"

#define WORLD_MIN    (Vector2){ -5000, -5000 }
#define WORLD_MAX    (Vector2){  5000,  5000 }
#define PREY_COUNT   100
#define PRED_COUNT   100

static Vector2 RandomPosition(void) {
    return (Vector2){
        (float)GetRandomValue(WORLD_MIN.x, WORLD_MAX.x),
        (float)GetRandomValue(WORLD_MIN.y, WORLD_MAX.y)
    };
}

int main(int argc, char* argv[]) {
    InitWindow(1920, 1080, "Ecosystem Sim");

    SetRandomSeed((unsigned int)time(NULL)); // different spawns every run

    UserCamera userCamera = CreateUserCamera((Vector2){ 0.0f, 0.0f });
    EntityManager* entityManager = CreateEntityManager(PREY_COUNT + PRED_COUNT);

    // spawn prey
    for (int i = 0; i < PREY_COUNT; i++) {
        Vector2 pos = RandomPosition();

        AddEntity(
            entityManager,
            CreatePrey(
                "Bunny",
                pos,
                150.0f,   // speed
                100,     // health
                50.0f // flee range
            )
        );
    }

    // spawn predators
    for (int i = 0; i < PRED_COUNT; i++) {
        Vector2 pos = RandomPosition();

        AddEntity(
            entityManager,
            CreatePredator(
                "Foxy",
                pos,
                200.0f,    // speed
                120,      // health
                75.0f  // hunt range
            )
        );
    }

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        UpdateUserCamera(&userCamera, deltaTime);
        UpdateEntities(entityManager, deltaTime);

        BeginDrawing();
            ClearBackground(DARKGREEN);

            BeginUserCameraMode(&userCamera);
                DrawEntities(entityManager);

                // draw world bounds
                DrawRectangleLinesEx(
                    (Rectangle){
                        WORLD_MIN.x,
                        WORLD_MIN.y,
                        WORLD_MAX.x - WORLD_MIN.x,
                        WORLD_MAX.y - WORLD_MIN.y
                    },
                    5.0f,
                    SKYBLUE
                );
            EndUserCameraMode();

            DrawFPS(10, 10);
        EndDrawing();
    }

    DestroyEntityManager(entityManager);
    CloseWindow();

    return 0;
}
