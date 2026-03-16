#include "ui.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* ---- Colour palette (8 swatches) ---- */
static const Uint8 PALETTE[8][3] = {
    {220,  60,  60},   /* red    */
    {220, 140,  40},   /* orange */
    {220, 210,  40},   /* yellow */
    { 60, 190,  70},   /* green  */
    { 60, 110, 220},   /* blue   */
    {160,  60, 220},   /* purple */
    {220, 220, 220},   /* white  */
    { 50, 210, 200},   /* cyan   */
};

/* ---- Slider descriptors ---- */
typedef struct { int y; const char *label; float min_v; float max_v; } SliderDef;

static const SliderDef SLIDERS[4] = {
    { 50, "GRAVITY",  50.0f, 2000.0f},
    { 93, "SIZE",      5.0f,   40.0f},
    {136, "BOUNCE",    0.1f,    1.0f},
    {179, "SPEED",    50.0f,  600.0f},
};

/* ---- Layout helpers ---- */
#define PAD           10
#define TRACK_MARGIN  36   /* right space reserved for value label */

static int track_x(int menu_x) { return menu_x + PAD; }
static int track_w(void)       { return MENU_WIDTH - PAD * 2 - TRACK_MARGIN; }

static int handle_x(int menu_x, float val, float mn, float mx_)
{
    float t = (val - mn) / (mx_ - mn);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return track_x(menu_x) + (int)(t * track_w());
}

static float *slider_ptr(UIState *s, int i)
{
    switch (i) {
    case 0: return &s->gravity;
    case 1: return &s->ball_radius;
    case 2: return &s->restitution;
    case 3: return &s->spawn_speed;
    default: return NULL;
    }
}

static float slider_from_x(int menu_x, int ex, int idx)
{
    float t = (float)(ex - track_x(menu_x)) / track_w();
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return SLIDERS[idx].min_v + t * (SLIDERS[idx].max_v - SLIDERS[idx].min_v);
}

/* ---- Draw helpers ---- */
static void sep(SDL_Renderer *r, int mx, int y)
{
    hlineRGBA(r, mx + PAD, mx + MENU_WIDTH - PAD, y, 55, 55, 80, 220);
}

static void label(SDL_Renderer *r, int x, int y, const char *s,
                  Uint8 R, Uint8 G, Uint8 B)
{
    stringRGBA(r, x,     y,     s, R, G, B, 255);
    stringRGBA(r, x + 1, y,     s, R, G, B, 200); /* slight bold */
    stringRGBA(r, x,     y + 1, s, R, G, B, 120);
}

static void draw_slider(SDL_Renderer *renderer, int mx, int idx, UIState *state)
{
    const SliderDef *sd = &SLIDERS[idx];
    float val = *slider_ptr(state, idx);

    int lx = track_x(mx);
    int ly = sd->y;
    int ty = ly + 14;   /* track centre y */
    int tw = track_w();
    int hx = handle_x(mx, val, sd->min_v, sd->max_v);

    /* label */
    label(renderer, lx, ly, sd->label, 160, 175, 210);

    /* track background */
    boxRGBA(renderer, lx, ty - 3, lx + tw, ty + 3, 45, 45, 65, 255);
    /* track fill */
    boxRGBA(renderer, lx, ty - 3, hx,      ty + 3, 70, 130, 215, 255);
    /* handle circle */
    filledCircleRGBA(renderer, hx, ty, 7, 190, 215, 255, 255);
    circleRGBA      (renderer, hx, ty, 7,  90, 140, 200, 255);

    /* value text */
    char buf[16];
    if (idx == 2)
        snprintf(buf, sizeof(buf), "%.2f", val);
    else if (idx == 0)
        snprintf(buf, sizeof(buf), "%.0f", val);
    else
        snprintf(buf, sizeof(buf), "%d",   (int)val);

    stringRGBA(renderer, lx + tw + 4, ty - 4, buf, 190, 200, 220, 255);
}

static void mini_shape(SDL_Renderer *renderer, int cx, int cy,
                       BallShape shape, bool selected)
{
    int bsz = 18;
    /* button background */
    Uint8 bg  = selected ? 75 : 38;
    Uint8 bdr = selected ? 200 : 70;
    boxRGBA      (renderer, cx - bsz, cy - bsz, cx + bsz, cy + bsz, bg, bg, bg + 20, 255);
    rectangleRGBA(renderer, cx - bsz, cy - bsz, cx + bsz, cy + bsz, bdr, bdr + 30, bdr + 80, 255);

    Sint16 vx[8], vy[8];
    int r = 12;
    Uint8 R = 185, G = 205, B = 255;

    switch (shape) {
    case SHAPE_CIRCLE:
        filledCircleRGBA(renderer, cx, cy, r, R, G, B, 255);
        break;
    case SHAPE_SQUARE:
        for (int i = 0; i < 4; i++) {
            float a = (float)M_PI / 4.0f + 2.0f * (float)M_PI * i / 4.0f;
            vx[i] = cx + (Sint16)(r * cosf(a));
            vy[i] = cy + (Sint16)(r * sinf(a));
        }
        filledPolygonRGBA(renderer, vx, vy, 4, R, G, B, 255);
        break;
    case SHAPE_TRIANGLE:
        for (int i = 0; i < 3; i++) {
            float a = -(float)M_PI / 2.0f + 2.0f * (float)M_PI * i / 3.0f;
            vx[i] = cx + (Sint16)(r * cosf(a));
            vy[i] = cy + (Sint16)(r * sinf(a));
        }
        filledPolygonRGBA(renderer, vx, vy, 3, R, G, B, 255);
        break;
    case SHAPE_DIAMOND:
        for (int i = 0; i < 4; i++) {
            float a = 2.0f * (float)M_PI * i / 4.0f;
            vx[i] = cx + (Sint16)(r * cosf(a));
            vy[i] = cy + (Sint16)(r * sinf(a));
        }
        filledPolygonRGBA(renderer, vx, vy, 4, R, G, B, 255);
        break;
    case SHAPE_PENTAGON:
        for (int i = 0; i < 5; i++) {
            float a = -(float)M_PI / 2.0f + 2.0f * (float)M_PI * i / 5.0f;
            vx[i] = cx + (Sint16)(r * cosf(a));
            vy[i] = cy + (Sint16)(r * sinf(a));
        }
        filledPolygonRGBA(renderer, vx, vy, 5, R, G, B, 255);
        break;
    default: break;
    }
}

/* ---- Public API ---- */

void ui_init(UIState *state)
{
    state->gravity          = 500.0f;
    state->ball_radius      = 15.0f;
    state->restitution      = 0.75f;
    state->spawn_speed      = 320.0f;
    state->shape            = SHAPE_CIRCLE;
    state->color_r          = PALETTE[4][0];
    state->color_g          = PALETTE[4][1];
    state->color_b          = PALETTE[4][2];
    state->clear_requested  = false;
    state->dragging_slider  = -1;
}

void ui_draw(SDL_Renderer *renderer, UIState *state, int win_w, int win_h,
             int ball_count)
{
    int mx = win_w - MENU_WIDTH;

    /* panel background */
    boxRGBA      (renderer, mx, 0, win_w, win_h, 16, 16, 26, 255);
    vlineRGBA    (renderer, mx, 0, win_h,         55, 55, 85, 255);

    /* title */
    label(renderer, mx + PAD,      8, "BALL",    100, 155, 220);
    label(renderer, mx + PAD + 40, 8, "PHYSICS", 215, 175,  70);
    sep(renderer, mx, 24);

    /* sliders */
    for (int i = 0; i < 4; i++)
        draw_slider(renderer, mx, i, state);

    /* ---- SHAPE section ---- */
    sep(renderer, mx, 210);
    label(renderer, mx + PAD, 218, "SHAPE", 160, 175, 210);

    int btn_gap = (MENU_WIDTH - PAD * 2) / SHAPE_COUNT;
    int shape_cy = 255;
    for (int i = 0; i < SHAPE_COUNT; i++) {
        int cx = mx + PAD + btn_gap * i + btn_gap / 2;
        mini_shape(renderer, cx, shape_cy, (BallShape)i, state->shape == (BallShape)i);
    }

    /* ---- COLOR section ---- */
    sep(renderer, mx, 282);
    label(renderer, mx + PAD, 290, "COLOR", 160, 175, 210);

    int swatch  = (MENU_WIDTH - PAD * 2) / 8;
    int col_y   = 308;
    for (int i = 0; i < 8; i++) {
        int sx  = mx + PAD + i * swatch;
        bool sel = (state->color_r == PALETTE[i][0] &&
                    state->color_g == PALETTE[i][1] &&
                    state->color_b == PALETTE[i][2]);
        boxRGBA      (renderer,
                      sx + 2, col_y + 2, sx + swatch - 2, col_y + swatch - 2,
                      PALETTE[i][0], PALETTE[i][1], PALETTE[i][2], 255);
        rectangleRGBA(renderer,
                      sx + 1, col_y + 1, sx + swatch - 2, col_y + swatch - 2,
                      sel ? 255 : 30, sel ? 255 : 30, sel ? 255 : 50, 255);
    }

    /* ---- CLEAR button ---- */
    int btn_y  = col_y + swatch + 16;
    int btn_x  = mx + PAD;
    int btn_bw = MENU_WIDTH - PAD * 2;
    sep(renderer, mx, btn_y - 8);

    boxRGBA      (renderer, btn_x, btn_y, btn_x + btn_bw, btn_y + 22, 75, 35, 35, 255);
    rectangleRGBA(renderer, btn_x, btn_y, btn_x + btn_bw, btn_y + 22, 180, 80, 80, 255);
    /* center "CLEAR ALL" — 9 chars × 8px = 72px */
    int label_cx = btn_x + (btn_bw - 72) / 2;
    label(renderer, label_cx, btn_y + 7, "CLEAR ALL", 215, 135, 135);

    /* ---- Ball counter ---- */
    char buf[40];
    snprintf(buf, sizeof(buf), "BALLS: %d / %d", ball_count, MAX_BALLS);
    stringRGBA(renderer, mx + PAD, btn_y + 30, buf, 110, 130, 155, 255);

    /* ---- Hint ---- */
    stringRGBA(renderer, mx + PAD, btn_y + 44, "Click sim to spawn", 55, 65, 85, 255);
    stringRGBA(renderer, mx + PAD, btn_y + 54, "ESC to quit",        55, 65, 85, 255);

    (void)win_h;
}

void ui_handle_event(SDL_Event *event, UIState *state, int win_w, int win_h)
{
    (void)win_h;
    int mx  = win_w - MENU_WIDTH;
    int tx  = track_x(mx);
    int tw  = track_w();

    switch (event->type) {

    case SDL_MOUSEBUTTONDOWN: {
        int ex = event->button.x;
        int ey = event->button.y;
        if (ex < mx) break; /* in sim area – ignore */

        /* sliders */
        for (int i = 0; i < 4; i++) {
            int ty = SLIDERS[i].y + 14;
            if (ey >= ty - 10 && ey <= ty + 10 &&
                ex >= tx - 6   && ex <= tx + tw + 6) {
                state->dragging_slider = i;
                *slider_ptr(state, i) = slider_from_x(mx, ex, i);
                break;
            }
        }

        /* shape buttons */
        int btn_gap  = (MENU_WIDTH - PAD * 2) / SHAPE_COUNT;
        int shape_cy = 255;
        for (int i = 0; i < SHAPE_COUNT; i++) {
            int cx = mx + PAD + btn_gap * i + btn_gap / 2;
            if (abs(ex - cx) <= 18 && abs(ey - shape_cy) <= 18)
                state->shape = (BallShape)i;
        }

        /* colour swatches */
        int swatch = (MENU_WIDTH - PAD * 2) / 8;
        int col_y  = 308;
        if (ey >= col_y && ey < col_y + swatch) {
            int ci = (ex - (mx + PAD)) / swatch;
            if (ci >= 0 && ci < 8) {
                state->color_r = PALETTE[ci][0];
                state->color_g = PALETTE[ci][1];
                state->color_b = PALETTE[ci][2];
            }
        }

        /* clear button */
        int btn_y  = col_y + swatch + 16;
        int btn_x  = mx + PAD;
        int btn_bw = MENU_WIDTH - PAD * 2;
        if (ex >= btn_x && ex <= btn_x + btn_bw &&
            ey >= btn_y && ey <= btn_y + 22)
            state->clear_requested = true;

        break;
    }

    case SDL_MOUSEMOTION:
        if (state->dragging_slider >= 0 && (event->motion.state & SDL_BUTTON_LMASK)) {
            int i = state->dragging_slider;
            *slider_ptr(state, i) = slider_from_x(mx, event->motion.x, i);
        }
        break;

    case SDL_MOUSEBUTTONUP:
        state->dragging_slider = -1;
        break;
    }
}
