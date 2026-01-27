#pragma once

#include <raylib.h>
#include "entity/entity.h"

#define QUADTREE_CAPACITY 5

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