#pragma once

#include "entity/entity.h"

#define PREDATOR_TEXTURE_PATH "assets/textures/kyluong_128.jpg"
#define PREY_TEXTURE_PATH     "assets/textures/chaey_128.jpg"

typedef struct {
    Entity **data;
    int size;
    int capacity;

    int free_count;
    int *free_slots;

    Texture2D preyTexture;
    Texture2D predatorTexture;
} EntityManager;

EntityManager* CreateEntityManager(int initial_capacity);
void DestroyEntityManager(EntityManager* manager);

int AddEntity(EntityManager* manager, Entity entity);
void RemoveEntity(EntityManager* manager, int index);
void UpdateEntities(EntityManager* manager, float deltaTime);
void DrawEntities(const EntityManager* manager);
