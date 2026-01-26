#include "entity/entity.h"
#include <raylib.h>

// create a prey
Entity CreatePrey(const char* name, Vector2 position, float speed, int health, float fleeRange) {
    Entity prey = CreateEntity(name, PREY, position, speed, health);

    prey.prey.fleeRange = fleeRange;

    return prey;
}

// update prey logic
void UpdatePrey(Entity *prey, float deltaTime) {
    // example logic placeholder:
    // move away from predators, eat grass, etc.
}

// draw prey
void DrawPrey(const Entity *prey, Texture2D* texture) {
    DrawTextureEx(
        *texture, 
        prey->position,
        0.0f,
        1.0f,
        WHITE
    );
}
