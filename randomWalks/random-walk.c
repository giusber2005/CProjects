#include "utils.h"
#include <stdint.h>

int movement_types[4][2] = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1}
};

int main(int argc, const char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL));

    int num_agents;
    if(argc == 1) {
        num_agents = 5;
    } else if(argc == 2) {
        num_agents = atoi(argv[1]);
    } else {
        printf("Usage: %s <num-of-agents>\n", argv[0]);
    }

    int agents[num_agents];
    int agentsPos[num_agents][2];
    for(int i = 0; i < num_agents; i++) {
        agents[i] = (rand() % POOL) + 1;
        agentsPos[i][0] = WIDTH / 2;
        agentsPos[i][1] = HEIGHT / 2;
    }

    uint8_t (*agentsColors)[4] = generate_colors(num_agents);

    SDL_Window *window = SDL_CreateWindow("Random Walks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int app_running = 1;
    SDL_Event event;

    int frameCount = 0;
    while(app_running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app_running = 0;
            }
        }

        frameCount++;

        uint8_t (*colors_pointer)[4] = agentsColors;
        for(int j = 0; j < num_agents; j++) {
            if(agents[j] == frameCount) {
                int movType = rand() % 4;
                thickLineRGBA(renderer,
                            agentsPos[j][0],
                            agentsPos[j][1],
                            agentsPos[j][0] + (STEP * movement_types[movType][0]),
                            agentsPos[j][1] + (STEP * movement_types[movType][1]), 
                            THICKNESS,
                            (*colors_pointer)[0],
                            (*colors_pointer)[1],
                            (*colors_pointer)[2],
                            (*colors_pointer)[3]);
                
                //Update walker position and next movement instant
                agentsPos[j][0] += (STEP * movement_types[movType][0]);
                agentsPos[j][1] += (STEP * movement_types[movType][1]);
                agents[j] += (rand() % POOL) + 1;
            }

            colors_pointer++;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}