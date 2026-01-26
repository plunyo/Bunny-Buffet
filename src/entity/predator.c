#include "entity/entity.h"

// create a predator
Entity CreatePredator(const char* name, Vector2 position, float speed, int health, float huntRange) {
    Entity predator = CreateEntity(name, PREDATOR, position, speed, health);

    predator.predator.huntRange = huntRange;

    return predator;
}

// update predator logic
void UpdatePredator(Entity *predator, float deltaTime) {
    // example logic placeholder:
    // move towards prey, reduce health if starving, etc.
}

// draw predator
void DrawPredator(const Entity* predator, Texture2D* texture) {
    DrawTextureEx(
        *texture, 
        predator->position,
        0.0f,
        1.0f,
        WHITE
    );
}