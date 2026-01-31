#pragma once

#include <raylib.h>
#include "entity/entity.h"

#define QUADTREE_CAPACITY 3

typedef struct QuadTree {
    Rectangle boundary;
    int count;
    Entity* entities[QUADTREE_CAPACITY];

    struct QuadTree* northeast;
    struct QuadTree* northwest;
    struct QuadTree* southeast;
    struct QuadTree* southwest;
} QuadTree;

QuadTree* CreateQuadTree(Rectangle boundary);
void SubdivideQuadTree(QuadTree* qt);
bool InsertEntity(QuadTree* qt, Entity* entity);
void QueryQuadTree(QuadTree* qt, Rectangle range, Entity** found, int* foundCount);
void ClearQuadTree(QuadTree* qt);
void DrawQuadTree(QuadTree* qt, int depth);
void DestroyQuadTree(QuadTree* qt);