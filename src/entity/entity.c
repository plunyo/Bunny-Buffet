#include "entity/entity.h"

#include <raylib.h>
#include <raymath.h>

static Vector2 GetWanderDirection(Vector2 currentDirection);

// updates entity based on type
void UpdateEntity(Entity *entity, float deltaTime) {
    entity->velocity = Vector2Scale(Vector2Scale(entity->direction, entity->speed), deltaTime);
    entity->position = Vector2Add(entity->position, entity->velocity);

    switch (entity->type) {
        case PREY:
            UpdatePrey(entity, deltaTime);
            break;
        case PREDATOR:
            UpdatePredator(entity, deltaTime);
            break;
    }
}

void UpdateEntityState(Entity *entity) {
    switch (entity->state) {
        case STATE_WANDERING:
            entity->direction = GetWanderDirection(entity->direction);
            break;
        default:
            switch (entity->type) {
                case PREY:
                    UpdatePreyState(entity);
                    break;
                case PREDATOR:
                    UpdatePredatorState(entity);
                    break;
            } 
    }
}

// draws entity based on type
void DrawEntity(const Entity* entity, Texture2D* texture) {
    switch (entity->type) {
        case PREY:
            DrawPrey(entity, texture);
            break;
        case PREDATOR:
            DrawPredator(entity, texture);
            break;
    }
}

// generic entity creation
Entity CreateEntity(const char* name, EntityType type, Vector2 position, float speed, int health) {
    Entity entity;

    entity.name = name;
    entity.type = type;
    entity.state = STATE_WANDERING;
    entity.position = position;
    entity.speed = speed;
    entity.health = health;

    entity.direction = Vector2Normalize((Vector2){
        GetRandomValue(-100,100),
        GetRandomValue(-100,100)
    });

    return entity;
}

static Vector2 GetWanderDirection(Vector2 currentDirection) {
    // get current angle
    float currentAngle = atan2f(currentDirection.y, currentDirection.x);

    // small random turn instead of full random direction
    float turn = (float)GetRandomValue(-1000, 1000) / 1000.0f;

    float newAngle = currentAngle + turn;

    return (Vector2){ cosf(newAngle), sinf(newAngle) };
}
