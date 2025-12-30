//
// Created by Lalith on 12/30/25.
//

#include "display.h"


Display::Display() :
    window(nullptr),
    renderer(nullptr),
    centerX(CENTER_X),
    centerY(CENTER_Y),
    scale(SCALE),
    tickSize(TICK_SIZE) {
}

Display::~Display() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void Display::initSDL() {
    int renderFlags = SDL_RENDERER_ACCELERATED;
    int windowsFlags = 0;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    window = SDL_CreateWindow("Function Generater",
        SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,SCREEN_HEIGHT,windowsFlags
        );

    if (!window) {
        std::cout << "Could not create window! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "Linear");
    renderer = SDL_CreateRenderer(window, -1, renderFlags);
    if (!renderer) {
        std::cout << "Could not create renderer! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-1);
    }
}


// void Display::mainLoop() {
//     SDL_Event event;
//     while (SDL_PollEvent(&event)) {
//         switch (event.type) {
//             case SDL_QUIT:
//                 std::cout << "Quitting..." << std::endl;
//                 exit(0);
//             default:
//                 break;
//         }
//     }
// }


void Display::prepareScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void Display::presentScreen() {
    SDL_RenderPresent(renderer);
}

void Display::graphLines() {
    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer, centerX, 0, centerX, SCREEN_HEIGHT);
    SDL_RenderDrawLine(renderer, 0, centerY, SCREEN_WIDTH, centerY);


    for (double i = scale; i < SCREEN_WIDTH / 2; i += scale) {
        SDL_RenderDrawLine(renderer,
            centerX + static_cast<int>(i),
            centerY - tickSize / 2,
            centerX + static_cast<int>(i),
            centerY + tickSize / 2);
        SDL_RenderDrawLine(renderer,
            centerX + static_cast<int>(i),
            centerY - tickSize / 2,
            centerX + static_cast<int>(i),
            centerY + tickSize / 2);
    }
    for (double i = scale; i < SCREEN_HEIGHT / 2; i += scale) {
        SDL_RenderDrawLine(renderer,
            centerX - tickSize / 2,
            centerY + static_cast<int>(i),
            centerX + tickSize / 2,
            centerY + static_cast<int>(i));
        SDL_RenderDrawLine(renderer,
            centerX - tickSize / 2,
            centerY - static_cast<int>(i),
            centerX + tickSize / 2,
            centerY + static_cast<int>(i)
            );
    }
}
