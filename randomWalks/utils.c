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