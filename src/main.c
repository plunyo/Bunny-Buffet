#include <raylib.h>
#include <time.h>
#include <stdio.h>
#include "user_camera/user_camera.h"
#include "entity/entity.h"
#include "entity_manager/entity_manager.h"
#include "quadtree/quadtree.h"

#define WORLD_MIN    (Vector2){ -100000, -100000 }
#define WORLD_MAX    (Vector2){  100000,  100000 }

#define WORLD_BOUNDS (Rectangle) {  \
    WORLD_MIN.x, WORLD_MIN.y,       \
    WORLD_MAX.x - WORLD_MIN.x,      \
    WORLD_MAX.y - WORLD_MIN.y       \
}

#define PREY_COUNT   2500
#define PRED_COUNT   2500

static Vector2 RandomPosition() {
    return (Vector2){
        (float)GetRandomValue(WORLD_MIN.x, WORLD_MAX.x),
        (float)GetRandomValue(WORLD_MIN.y, WORLD_MAX.y)
    };
}

static void InitEntities(EntityManager* entityManager) {
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
}

static void SetupWindow() {
    InitWindow(1920, 1080, "Ecosystem Sim");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

int main(int argc, char* argv[]) {
    SetupWindow();

    SetRandomSeed((unsigned int)time(NULL)); // different spawns every run

    UserCamera userCamera = CreateUserCamera((Vector2){ 0.0f, 0.0f });
    EntityManager* entityManager = CreateEntityManager(PREY_COUNT + PRED_COUNT);
    QuadTree* rootQuadTree = CreateQuadTree(WORLD_BOUNDS);

    InitEntities(entityManager);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        //fullscreen ig
        if (IsKeyDown(KEY_F11)) SetWindowState(FLAG_FULLSCREEN_MODE) GET;

        UpdateUserCamera(&userCamera, deltaTime);
        UpdateEntities(entityManager, deltaTime);
        BounceEntitiesInBounds(entityManager, WORLD_BOUNDS);

        ClearQuadTree(rootQuadTree);

        for (int i = 0; i < entityManager->size; i++) {
            InsertEntity(rootQuadTree, entityManager->data[i]);
        }

        BeginDrawing();
            ClearBackground(DARKGREEN);

            BeginUserCameraMode(&userCamera);
                DrawEntities(entityManager, rootQuadTree, &userCamera);
                //DrawQuadTree(rootQuadTree, 0);
            EndUserCameraMode();

            DrawFPS(10, 10);
        EndDrawing();
    }

    DestroyEntityManager(entityManager);
    CloseWindow();

    return 0;
}
