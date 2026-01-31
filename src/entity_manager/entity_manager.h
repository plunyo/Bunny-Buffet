#pragma once

#include "user_camera/user_camera.h"
#include "entity/entity.h"
#include "quadtree/quadtree.h"
#include "timer/timer.h"

#define PREDATOR_TEXTURE_PATH "assets/textures/kyluong_256.jpg"
#define PREY_TEXTURE_PATH     "assets/textures/chaey_256.jpg"

#define MAX_VISIBLE 10000

typedef struct {
    Entity **data;
    int size;
    int capacity;

    int free_count;
    int *free_slots;

    QuadTree* quadTree;

    Timer updateEntityStatesTimer;

    Texture2D preyTexture;
    Texture2D predatorTexture;
} EntityManager;

EntityManager* CreateEntityManager(int initial_capacity);
void DestroyEntityManager(EntityManager* manager);

int AddEntity(EntityManager* manager, Entity entity);
void RemoveEntity(EntityManager* manager, int index);
void UpdateEntities(EntityManager* manager, float deltaTime);
void BounceEntitiesInBounds(EntityManager* manager, Rectangle worldBounds);
void DrawEntities(const EntityManager* manager, QuadTree* quadTree, UserCamera* cam);
