#pragma once

#include <raylib.h>

// types of entities
typedef enum EntityType {
    PREY,
    PREDATOR
} EntityType;

// main entity struct
typedef struct Entity {
    const char* name;
    EntityType type;

    Vector2 position;
    float speed;
    int health;

    union {
        struct {
            float fleeRange; // was predRange
        } prey;

        struct {
            float huntRange;
        } predator;
    };
} Entity;

// generic entity functions
Entity CreateEntity(const char* name, EntityType type, Vector2 position, float speed, int health);
void UpdateEntity(Entity* entity, float deltaTime);

// prey-specific functions
Entity CreatePrey(const char* name, Vector2 position, float speed, int health, float fleeRange);
void UpdatePrey(Entity* prey, float deltaTime);
void DrawPrey(const Entity* prey, Texture2D* texture);

// predator-specific functions
Entity CreatePredator(const char* name, Vector2 position, float speed, int health, float huntRange);
void UpdatePredator(Entity* predator, float deltaTime);
void DrawPredator(const Entity* predator, Texture2D* texture);
