#pragma once

#include <raylib.h>

#define ENTITY_SIZE 256.0f

typedef enum EntityType {
    PREY,
    PREDATOR
} EntityType;

typedef enum EntityState {
    STATE_WANDERING,
    STATE_HUNTING,
    STATE_FLEEING,
} EntityState;

typedef struct Entity {
    const char* name;
    EntityType type;
    EntityState state;

    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    float speed;
    int health;

    union {
        struct {
            float fleeRange;
        } prey;

        struct {
            float huntRange;
        } predator;
    };
} Entity;

// generic entity functions
Entity CreateEntity(const char* name, EntityType type, Vector2 position, float speed, int health);
void UpdateEntity(Entity* entity, float deltaTime);
void UpdateEntityState(Entity* entity);

// prey-specific functions
Entity CreatePrey(const char* name, Vector2 position, float speed, int health, float fleeRange);
void UpdatePrey(Entity* prey, float deltaTime);
void UpdatePreyState(Entity* prey);
void DrawPrey(const Entity* prey, Texture2D* texture);

// predator-specific functions
Entity CreatePredator(const char* name, Vector2 position, float speed, int health, float huntRange);
void UpdatePredator(Entity* predator, float deltaTime);
void UpdatePredatorState(Entity* predator);
void DrawPredator(const Entity* predator, Texture2D* texture);
