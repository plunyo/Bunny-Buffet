#include "entity_manager/entity_manager.h"
#include "quadtree/quadtree.h"
#include "user_camera/user_camera.h"

#include <raylib.h>
#include <stdlib.h>
#include <rlgl.h>

static void OnEntityStatesTimerFinished(void* context);

EntityManager* CreateEntityManager(int initial_capacity) {
    EntityManager* manager = (EntityManager*)MemAlloc(sizeof(EntityManager));

    manager->data = (Entity**)MemAlloc(sizeof(Entity*) * initial_capacity);
    manager->size = 0;
    manager->capacity = initial_capacity;
    manager->free_count = 0;
    manager->free_slots = (int*)MemAlloc(sizeof(int) * initial_capacity);

    manager->preyTexture = LoadTexture(PREY_TEXTURE_PATH);
    manager->predatorTexture = LoadTexture(PREDATOR_TEXTURE_PATH);

    manager->entityStatesTimer = CreateTimer(
        1.0f,
        true, 
        OnEntityStatesTimerFinished, 
        manager
    );

    return manager;
}

// destroy manager
void DestroyEntityManager(EntityManager* manager) {
    for (int i = 0; i < manager->size; i++) {
        if (manager->data[i] == NULL) continue;
    
        MemFree(manager->data[i]);
    }

    MemFree(manager->data);
    MemFree(manager->free_slots);

    UnloadTexture(manager->preyTexture);
    UnloadTexture(manager->predatorTexture);

    MemFree(manager);
}

// add entity
int AddEntity(EntityManager* manager, Entity entity) {
    int index;

    if (manager->free_count > 0) {
        index = manager->free_slots[--manager->free_count];
    } else {
        if (manager->size >= manager->capacity) {
            manager->capacity *= 2;
            manager->data = (Entity**)MemRealloc(manager->data, sizeof(Entity*) * manager->capacity);
            manager->free_slots = (int*)MemRealloc(manager->free_slots, sizeof(int) * manager->capacity);
        }

        index = manager->size++;
    }

    Entity* new_entity = (Entity*)MemAlloc(sizeof(Entity));
    *new_entity = entity;
    manager->data[index] = new_entity;

    return index;
}

void RemoveEntity(EntityManager* manager, int index) {
    if (index < 0 || index >= manager->size || manager->data[index] == NULL) {
        return;
    }

    MemFree(manager->data[index]);
    manager->data[index] = NULL;
    manager->free_slots[manager->free_count++] = index;
}

void UpdateEntities(EntityManager* manager, float deltaTime) {
    UpdateTimer(&manager->entityStatesTimer, deltaTime);

    for (int i = 0; i < manager->size; i++) {
        if (manager->data[i] == NULL) continue;
        
        UpdateEntity(manager->data[i], deltaTime);
    }
}

void BounceEntitiesInBounds(EntityManager* manager, Rectangle worldBounds) {
    for (int i = 0; i < manager->size; i++) {
        Entity* entity = manager->data[i];
        if (!entity) continue;

        // bounce x
        if (entity->position.x < worldBounds.x) { entity->position.x = worldBounds.x; entity->velocity.x *= -1; }
        if (entity->position.x > worldBounds.x + worldBounds.width) { 
            entity->position.x = worldBounds.x + worldBounds.width; 
            entity->velocity.x *= -1; 
        }

        // bounce y
        if (entity->position.y < worldBounds.y) { entity->position.y = worldBounds.y; entity->velocity.y *= -1; }
        if (entity->position.y > worldBounds.y + worldBounds.height) { 
            entity->position.y = worldBounds.y + worldBounds.height; 
            entity->velocity.y *= -1; 
        }
    }
}

// draw all entities
void DrawEntities(const EntityManager* manager, QuadTree* quadTree, UserCamera* cam) {
    Entity** visible = malloc(sizeof(Entity*) * MAX_VISIBLE);
    int visibleCount = 0;
    QueryQuadTree(quadTree, GetUserCameraRect(cam), visible, &visibleCount);
        
    for (int i = 0; i < visibleCount; i++) {
        Entity* entity = visible[i];

        switch (entity->type) {
            case PREY:
                DrawPrey(entity, (Texture2D*)&manager->preyTexture);
                break;
            case PREDATOR:
                DrawPredator(entity, (Texture2D*)&manager->predatorTexture);
                break;
        }
    }
}

static void OnEntityStatesTimerFinished(void* context) {
    EntityManager* manager = (EntityManager*)context;

    for (int i = 0; i < manager->size; i++) {
        if (manager->data[i] != NULL) {
            UpdateEntityState(manager->data[i]);
        }
    }
}