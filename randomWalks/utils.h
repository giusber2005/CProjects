#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define WIDTH 900
#define HEIGHT 600
#define POOL 5
#define STEP 2
#define THICKNESS 2

uint8_t (*generate_colors(int walkersNum))[4];
