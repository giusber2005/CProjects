#pragma once

#include <SDL2/SDL.h>
#include "ball.h"

#define MENU_WIDTH 240

typedef struct {
    float gravity;       /* pixels/s²: 50 - 2000            */
    float ball_radius;   /* pixels:    5  - 40              */
    float restitution;   /* 0.0 - 1.0                       */
    float spawn_speed;   /* initial speed, pixels/s: 50-600 */
    BallShape shape;
    Uint8 color_r, color_g, color_b;
    bool  clear_requested;
    int   dragging_slider; /* -1 = none, 0-3 active */
} UIState;

void ui_init(UIState *state);
void ui_draw(SDL_Renderer *renderer, UIState *state, int win_w, int win_h, int ball_count);
void ui_handle_event(SDL_Event *event, UIState *state, int win_w, int win_h);
