#include "ball.h"
#include "ui.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define INITIAL_W  1100
#define INITIAL_H   700
#define TARGET_FPS   60

static Ball  balls[MAX_BALLS];
static int   ball_count = 0;

/* ---- Background grid ---- */
static void draw_grid(SDL_Renderer *renderer, int sim_w, int win_h)
{
    SDL_SetRenderDrawColor(renderer, 22, 22, 36, 255);
    for (int x = 0; x < sim_w; x += 60)
        SDL_RenderDrawLine(renderer, x, 0, x, win_h);
    for (int y = 0; y < win_h; y += 60)
        SDL_RenderDrawLine(renderer, 0, y, sim_w, y);
}

/* ---- Spawn a ball at (px, py) with an upward-biased random velocity ---- */
static void spawn_ball(float px, float py, UIState *state)
{
    if (ball_count >= MAX_BALLS) return;

    Ball *b = &balls[ball_count++];
    b->x      = px;
    b->y      = py;
    b->radius = state->ball_radius;
    b->shape  = state->shape;
    b->r      = state->color_r;
    b->g      = state->color_g;
    b->b      = state->color_b;
    b->active = true;

    /* random direction centred on straight up, ±54° spread */
    float spread = (float)M_PI * 0.30f;
    float angle  = -(float)M_PI / 2.0f +
                   ((float)rand() / RAND_MAX - 0.5f) * 2.0f * spread;
    float speed  = state->spawn_speed *
                   (0.85f + 0.30f * (float)rand() / RAND_MAX);

    b->vx = speed * cosf(angle);
    b->vy = speed * sinf(angle);
}

/* ---- Main ---- */
int main(void)
{
    srand((unsigned)time(NULL));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window   *window   = SDL_CreateWindow(
        "Bouncing Balls",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        INITIAL_W, INITIAL_H,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    UIState ui;
    ui_init(&ui);
    memset(balls, 0, sizeof(balls));

    Uint32 last_ticks = SDL_GetTicks();
    bool   running    = true;

    while (running) {

        /* delta time --------------------------------------------------------*/
        Uint32 now = SDL_GetTicks();
        float  dt  = (now - last_ticks) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;   /* cap to avoid tunnelling */
        last_ticks = now;

        /* window dimensions -------------------------------------------------*/
        int win_w, win_h;
        SDL_GetWindowSize(window, &win_w, &win_h);
        int sim_w = win_w - MENU_WIDTH;   /* simulation area width */

        /* events ------------------------------------------------------------*/
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                continue;
            }
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
                continue;
            }

            /* let the side-menu handle it first */
            ui_handle_event(&event, &ui, win_w, win_h);

            /* spawn on left-click inside the simulation area */
            if (event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.button == SDL_BUTTON_LEFT &&
                event.button.x < sim_w)
            {
                spawn_ball((float)event.button.x,
                           (float)event.button.y, &ui);
            }
        }

        /* clear all ---------------------------------------------------------*/
        if (ui.clear_requested) {
            memset(balls, 0, sizeof(balls));
            ball_count           = 0;
            ui.clear_requested   = false;
        }

        /* update physics ----------------------------------------------------*/
        for (int i = 0; i < ball_count; i++)
            ball_update(&balls[i], dt, ui.gravity, ui.restitution,
                        sim_w, win_h);

        /* render ------------------------------------------------------------*/
        SDL_SetRenderDrawColor(renderer, 10, 10, 18, 255);
        SDL_RenderClear(renderer);

        draw_grid(renderer, sim_w, win_h);

        for (int i = 0; i < ball_count; i++)
            ball_draw(renderer, &balls[i]);

        ui_draw(renderer, &ui, win_w, win_h, ball_count);

        SDL_RenderPresent(renderer);

        /* manual FPS cap (vsync fallback) -----------------------------------*/
        Uint32 frame_ms = SDL_GetTicks() - now;
        if (frame_ms < 1000 / TARGET_FPS)
            SDL_Delay(1000 / TARGET_FPS - frame_ms);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
