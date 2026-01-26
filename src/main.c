#include <raylib.h>
#include "entity/entity.h"
#include "entity_manager/entity_manager.h"

int main(int argc, char* argv[]) {
    InitWindow(1920, 1080, "My Game");

    EntityManager* entityManager = CreateEntityManager(10);

    AddEntity(
        entityManager, 
        CreatePrey(
            "Bunny",
            (Vector2){200.0f, 200.0f},
            150.0f,
            100,
            50.0f  // flee range
        )
    );

    AddEntity(
        entityManager, 
        CreatePredator(
            "Foxy",
            (Vector2){500.0f, 300.0f},
            200.0f,
            120,
            75.0f  // hunt range
        )
    );

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        UpdateEntities(entityManager, deltaTime);

        BeginDrawing();
            ClearBackground(GREEN);

            DrawEntities(entityManager);
    
            DrawFPS(10, 10);
        EndDrawing();
    }

    DestroyEntityManager(entityManager);
    CloseWindow();

    return 0;
}
