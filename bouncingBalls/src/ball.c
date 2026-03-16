#include "ball.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Build vertex arrays for a regular n-gon centered at (cx,cy) with given radius. */
static void poly_verts(Sint16 *vx, Sint16 *vy, int n,
                       float cx, float cy, float r, float angle_offset)
{
    for (int i = 0; i < n; i++) {
        float a = angle_offset + 2.0f * (float)M_PI * i / n;
        vx[i] = (Sint16)(cx + r * cosf(a));
        vy[i] = (Sint16)(cy + r * sinf(a));
    }
}

void ball_draw(SDL_Renderer *renderer, const Ball *b)
{
    if (!b->active) return;

    Sint16 x = (Sint16)b->x;
    Sint16 y = (Sint16)b->y;
    Sint16 rad = (Sint16)b->radius;
    Uint8  R = b->r, G = b->g, B = b->b;
    float  fr = b->radius;

    Sint16 vx[8], vy[8];

    switch (b->shape) {

    case SHAPE_CIRCLE:
        filledCircleRGBA(renderer, x, y, rad, R, G, B, 255);
        circleRGBA      (renderer, x, y, rad, 255, 255, 255, 50);
        break;

    case SHAPE_SQUARE:
        /* n=4, offset=π/4 → flat sides axis-aligned */
        poly_verts(vx, vy, 4, b->x, b->y, fr, (float)M_PI / 4.0f);
        filledPolygonRGBA(renderer, vx, vy, 4, R, G, B, 255);
        polygonRGBA      (renderer, vx, vy, 4, 255, 255, 255, 50);
        break;

    case SHAPE_TRIANGLE:
        /* n=3, offset=-π/2 → apex pointing up */
        poly_verts(vx, vy, 3, b->x, b->y, fr, -(float)M_PI / 2.0f);
        filledPolygonRGBA(renderer, vx, vy, 3, R, G, B, 255);
        polygonRGBA      (renderer, vx, vy, 3, 255, 255, 255, 50);
        break;

    case SHAPE_DIAMOND:
        /* n=4, offset=0 → vertices at cardinal directions */
        poly_verts(vx, vy, 4, b->x, b->y, fr, 0.0f);
        filledPolygonRGBA(renderer, vx, vy, 4, R, G, B, 255);
        polygonRGBA      (renderer, vx, vy, 4, 255, 255, 255, 50);
        break;

    case SHAPE_PENTAGON:
        /* n=5, offset=-π/2 → flat base at bottom */
        poly_verts(vx, vy, 5, b->x, b->y, fr, -(float)M_PI / 2.0f);
        filledPolygonRGBA(renderer, vx, vy, 5, R, G, B, 255);
        polygonRGBA      (renderer, vx, vy, 5, 255, 255, 255, 50);
        break;

    default:
        filledCircleRGBA(renderer, x, y, rad, R, G, B, 255);
        break;
    }
}

void ball_update(Ball *b, float dt, float gravity, float restitution,
                 int sim_w, int sim_h)
{
    if (!b->active) return;

    /* gravity */
    b->vy += gravity * dt;

    /* integrate */
    b->x += b->vx * dt;
    b->y += b->vy * dt;

    float r = b->radius;

    /* floor */
    if (b->y + r >= (float)sim_h) {
        b->y  = (float)sim_h - r;
        b->vy = -fabsf(b->vy) * restitution;
        b->vx *= 0.98f; /* rolling friction */
        if (fabsf(b->vy) < 2.0f) b->vy = 0.0f;
    }
    /* ceiling */
    if (b->y - r <= 0.0f) {
        b->y  = r;
        b->vy =  fabsf(b->vy) * restitution;
    }
    /* left wall */
    if (b->x - r <= 0.0f) {
        b->x  = r;
        b->vx =  fabsf(b->vx) * restitution;
    }
    /* right wall */
    if (b->x + r >= (float)sim_w) {
        b->x  = (float)sim_w - r;
        b->vx = -fabsf(b->vx) * restitution;
    }
}
