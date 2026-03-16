#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"utlist.h"

#define WINDOW_TITLE "Projector"
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define DENSITY 0.8

typedef struct PhasorStruct {
    double pulsation;
    double amplitude;
    double origin;
    double shift;
    struct PhasorStruct* next;
} Phasor;

typedef struct FuncStruct {
    double (*func)(double);
    struct FuncStruct* next;
} Func;

typedef struct GraphStruct {
    SDL_Point origin;
    double length;
    Func* funcList;
    Phasor* phasorList;
    struct GraphStruct* next;
} Graph;

void graph_generator(SDL_Renderer** renderer, Graph graph);
void projector(SDL_Renderer** renderer, double (*func)(double));
void phasor(SDL_Renderer** renderer, Phasor phasor);
void gatherer(Phasor* phasors, Graph* graphs);
void window_manager(SDL_Renderer** renderer, Graph* graphs);
void free_everything(Graph* graphs, Phasor* phasors, Func* funcs);
