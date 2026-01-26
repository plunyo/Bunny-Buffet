#include "entity_manager/entity_manager.h"

#include <raylib.h>
#include <stdlib.h>

// create manager
EntityManager* CreateEntityManager(int initial_capacity) {
    EntityManager* manager = (EntityManager*)MemAlloc(sizeof(EntityManager));

    manager->data = (Entity**)MemAlloc(sizeof(Entity*) * initial_capacity);
    manager->size = 0;
    manager->capacity = initial_capacity;
    manager->free_count = 0;
    manager->free_slots = (int*)MemAlloc(sizeof(int) * initial_capacity);

    manager->preyTexture = LoadTexture(PREY_TEXTURE_PATH);
    manager->predatorTexture = LoadTexture(PREDATOR_TEXTURE_PATH);

    return manager;
}

// destroy manager
void DestroyEntityManager(EntityManager* manager) {
    for (int i = 0; i < manager->size; i++) {
        if (manager->data[i] != NULL) {
            MemFree(manager->data[i]);
        }
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

// remove entity
void RemoveEntity(EntityManager* manager, int index) {
    if (index < 0 || index >= manager->size || manager->data[index] == NULL) {
        return;
    }

    MemFree(manager->data[index]);
    manager->data[index] = NULL;
    manager->free_slots[manager->free_count++] = index;
}

// update all entities
void UpdateEntities(EntityManager* manager, float deltaTime) {
    for (int i = 0; i < manager->size; i++) {
        if (manager->data[i] != NULL) {
            UpdateEntity(manager->data[i], deltaTime);
        }
    }
}

// draw all entities
void DrawEntities(const EntityManager* manager) {
    for (int i = 0; i < manager->size; i++) {
        if (manager->data[i] != NULL) {
            Entity* entity = manager->data[i];
    
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
}
