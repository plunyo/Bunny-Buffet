#include "entity/entity.h"

// updates entity based on type
void UpdateEntity(Entity *entity, float deltaTime)
{
    switch (entity->type) {
        case PREY:
            UpdatePrey(entity, deltaTime);
            break;
        case PREDATOR:
            UpdatePredator(entity, deltaTime);
            break;
    }
}

// draws entity based on type
void DrawEntity(const Entity* entity, Texture2D* texture)
{
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
    entity.position = position;
    entity.speed = speed;
    entity.health = health;

    return entity;
}
