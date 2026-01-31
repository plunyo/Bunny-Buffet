#include "quadtree/quadtree.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

static const Color palette[] = { DARKBLUE, BLUE, SKYBLUE, GREEN, LIME, YELLOW, ORANGE, RED };
static const int paletteSize = sizeof(palette) / sizeof(palette[0]);

QuadTree* CreateQuadTree(Rectangle boundary) {
    QuadTree* qt = calloc(1, sizeof(QuadTree));

    qt->boundary = boundary;
    qt->count = 0;

    qt->northeast = NULL;
    qt->northwest = NULL;
    qt->southeast = NULL;
    qt->southwest = NULL;

    return qt;
}

void SubdivideQuadTree(QuadTree* qt) {
    float x = qt->boundary.x;
    float y = qt->boundary.y;
    float w = qt->boundary.width / 2.0f;
    float h = qt->boundary.height / 2.0f;

    qt->northeast = CreateQuadTree((Rectangle){ x + w, y,     w, h });
    qt->northwest = CreateQuadTree((Rectangle){ x,     y,     w, h });
    qt->southeast = CreateQuadTree((Rectangle){ x + w, y + h, w, h });
    qt->southwest = CreateQuadTree((Rectangle){ x,     y + h, w, h });
}

bool InsertEntity(QuadTree* qt, Entity* entity) {
    if (!CheckCollisionPointRec(entity->position, qt->boundary)) {
        return false;
    }

    if (qt->count < QUADTREE_CAPACITY && qt->northeast == NULL) {
        qt->entities[qt->count++] = entity;
        return true;
    }

    if (qt->northeast == NULL) {
        SubdivideQuadTree(qt);

        for (int i = 0; i < qt->count; i++) {
            Entity* e = qt->entities[i];

            if (!InsertEntity(qt->northeast, e) &&
                !InsertEntity(qt->northwest, e) &&
                !InsertEntity(qt->southeast, e) &&
                !InsertEntity(qt->southwest, e)) {
            }
        }

        qt->count = 0;
    }

    if (InsertEntity(qt->northeast, entity)) return true;
    if (InsertEntity(qt->northwest, entity)) return true;
    if (InsertEntity(qt->southeast, entity)) return true;
    if (InsertEntity(qt->southwest, entity)) return true;

    return false;
}

void QueryQuadTree(QuadTree* qt, Rectangle range, Entity** found, int* foundCount) {
    if (!CheckCollisionRecs(qt->boundary, range)) return;
    
    for (int i = 0; i < qt->count; i++) {
        if (CheckCollisionPointRec(qt->entities[i]->position, range)) {
            found[(*foundCount)++] = qt->entities[i];
        }
    }

    // If no children, we're done
    if (qt->northeast == NULL) return;

    QueryQuadTree(qt->northeast, range, found, foundCount);
    QueryQuadTree(qt->northwest, range, found, foundCount);
    QueryQuadTree(qt->southeast, range, found, foundCount);
    QueryQuadTree(qt->southwest, range, found, foundCount);
}

void ClearQuadTree(QuadTree* qt) {
    qt->count = 0;

    if (qt->northeast != NULL) {
        ClearQuadTree(qt->northeast);
        ClearQuadTree(qt->northwest);
        ClearQuadTree(qt->southeast);
        ClearQuadTree(qt->southwest);
    }
}

void DrawQuadTree(QuadTree* qt, int depth) {
    if (!qt) return;

    // skip tiny nodes
    if (qt->boundary.width < 5 || qt->boundary.height < 5) return;

    Color color = palette[depth % paletteSize];

    float thickness = 20.0f - depth;
    if (thickness < 1.0f) thickness = 1.0f;

    DrawRectangleLinesEx(qt->boundary, thickness, ColorAlpha(color, 0.4f));

    Vector2 center = { qt->boundary.x + qt->boundary.width / 2.0f,
                       qt->boundary.y + qt->boundary.height / 2.0f };
    DrawText(TextFormat("%d", qt->count), (int)center.x - 20, (int)center.y - 20, 40, color);

    if (qt->northeast) DrawQuadTree(qt->northeast, depth + 1);
    if (qt->northwest) DrawQuadTree(qt->northwest, depth + 1);
    if (qt->southeast) DrawQuadTree(qt->southeast, depth + 1);
    if (qt->southwest) DrawQuadTree(qt->southwest, depth + 1);
}

void DestroyQuadTree(QuadTree* qt) {
    if (qt == NULL) return;

    DestroyQuadTree(qt->northeast);
    DestroyQuadTree(qt->northwest);
    DestroyQuadTree(qt->southeast);
    DestroyQuadTree(qt->southwest);

    MemFree(qt);
}