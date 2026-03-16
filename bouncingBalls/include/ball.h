#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_BALLS 500

typedef enum {
    SHAPE_CIRCLE   = 0,
    SHAPE_SQUARE   = 1,
    SHAPE_TRIANGLE = 2,
    SHAPE_DIAMOND  = 3,
    SHAPE_PENTAGON = 4,
    SHAPE_COUNT    = 5
} BallShape;

typedef struct {
    float x, y;
    float vx, vy;
    float radius;
    BallShape shape;
    Uint8 r, g, b;
    bool active;
} Ball;

void ball_draw(SDL_Renderer *renderer, const Ball *b);
void ball_update(Ball *b, float dt, float gravity, float restitution, int sim_w, int sim_h);
