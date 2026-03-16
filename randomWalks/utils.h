#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_rect.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define WIDTH 900
#define HEIGHT 600
#define POOL 5
#define STEP 2
#define THICKNESS 2
#define MARGIN 10
#define SPAWN_MARGIN 50

typedef struct lineCoordStruct {
    SDL_Point a, b;
} lineCoord;

uint8_t (*generate_colors(int walkersNum))[4];
void drawLine(SDL_Renderer* renderer, lineCoord coords);
void draw_graph(SDL_Renderer* renderer, int dims);
