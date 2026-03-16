#include "utils.h"

uint8_t (*generate_colors(int walkersNum))[4] {
    if (walkersNum <= 0) return NULL;

    uint8_t (*colors)[4] = malloc((size_t)walkersNum * sizeof *colors);
    if (!colors) return NULL;

    static int seeded = 0;
    if (!seeded) {
        srand((unsigned)time(NULL));
        seeded = 1;
    }

    for (int i = 0; i < walkersNum; i++) {
        int max_idx = rand() % 3;
        for (int c = 0; c < 3; c++) {
            if (c == max_idx) {
                colors[i][c] = 255;                  // guaranteed max channel
            } else {
                colors[i][c] = (uint8_t)(128 + rand() % 128); // bright range
            }
        }
        colors[i][3] = 255; // alpha
    }
    return colors;
}

void drawLine(SDL_Renderer* renderer, lineCoord coords) {
    SDL_RenderDrawLine(renderer, coords.a.x, coords.a.y, coords.b.x, coords.b.y);
}

void draw_graph(SDL_Renderer* renderer, int dims) {
    lineCoord coords;
    if(dims == 2) {
        coords.a = (SDL_Point){WIDTH/2, 0};
        coords.b = (SDL_Point){WIDTH/2,  HEIGHT};
        drawLine(renderer, coords);

        coords.a = (SDL_Point){0, HEIGHT/2};
        coords.b = (SDL_Point){WIDTH, HEIGHT/2};
        drawLine(renderer, coords);
    } else {
        coords.a = (SDL_Point){MARGIN, HEIGHT - MARGIN};
        coords.b = (SDL_Point){WIDTH - MARGIN,  MARGIN};
        drawLine(renderer, coords);

        coords.b = (SDL_Point){MARGIN,  MARGIN};
        drawLine(renderer, coords);

        coords.b = (SDL_Point){WIDTH - MARGIN,  HEIGHT - MARGIN};
        drawLine(renderer, coords);
    }
}


