//
// Created by darkrai on 12/20/25.
//

#ifndef FUNCTION_GENERATER_MAIN_H
#define FUNCTION_GENERATER_MAIN_H
#include "lib/tinyexpr.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>
#include "defs.h"
#endif //FUNCTION_GENERATER_MAIN_H


inline struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} app;

inline struct {
    double x{0};
    double y{0};
}function;

enum Mode {
    Y_EQUALS_X,
    X_EQUALS_Y,
};

