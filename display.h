//
// Created by Lalith on 12/30/25.
//

#ifndef FUNCTION_GENERATER_DISPLAY_H
#define FUNCTION_GENERATER_DISPLAY_H

#include "defs.h"

class Display {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int centerX;
    int centerY;
    double scale;
    int tickSize;

public:
    Display();
    ~Display();

    // Delete copy constructor and assignment operator
    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;

    void initSDL();
    void mainLoop();
    void prepareScreen();
    void presentScreen();
    void graphLines();

    // Getters
    SDL_Renderer* getRenderer() const { return renderer; }
    SDL_Window* getWindow() const { return window; }
};


#endif //FUNCTION_GENERATER_DISPLAY_H