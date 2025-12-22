#include "main.h"

void initSDL() {
    int renderFlags{0}, windowsFlags{0};
    renderFlags = SDL_RENDERER_ACCELERATED;
    windowsFlags = 0;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    app.window = SDL_CreateWindow("fUNCTION Generater",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,windowsFlags);
    if (!app.window) {
        std::cout<<"Could not create window! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "Linear");
    app.renderer = SDL_CreateRenderer(app.window, -1, renderFlags);
    if (!app.renderer) {
        std::cout << "Could not create renderer! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
}


void mainLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                std::cout << "Quitting" << std::endl;
                exit(0);
            default:
                break;
        }
    }
}

void prepareScreen(void) {
    SDL_SetRenderDrawColor(app.renderer,0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
}

void presentScreen() {
    SDL_RenderPresent(app.renderer);
}

void graphLines() {
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);//white colour
    SDL_RenderDrawLine(app.renderer, centerX, 0, centerX, 720); // Y-axis
    SDL_RenderDrawLine(app.renderer, 0, centerY, 1280, centerY); // X-axis
    // DRAW X-AXIS TICKS (Going Right and Left from Center)
    for (double i = scale; i < 640; i += scale) {
        // Right side ticks
        SDL_RenderDrawLine(app.renderer, centerX + static_cast<int>(i), centerY - tickSize/2, centerX + static_cast<int>(i), centerY + tickSize/2);
        // Left side ticks
        SDL_RenderDrawLine(app.renderer, centerX - static_cast<int>(i), centerY - tickSize/2, centerX - static_cast<int>(i), centerY + tickSize/2);
    }
    // DRAW Y-AXIS TICKS (Going Up and Down from Center)
    for (double i = scale; i < 360; i += scale) {
        // Down ticks
        SDL_RenderDrawLine(app.renderer, centerX - tickSize/2, centerY + static_cast<int>(i), centerX + tickSize/2, centerY + static_cast<int>(i));
        // Up ticks
        SDL_RenderDrawLine(app.renderer, centerX - tickSize/2, centerY - static_cast<int>(i), centerX + tickSize/2, centerY - static_cast<int>(i));
    }
}
std::tuple<Mode,std::string>parserInput(std
    ::string& inputEquation) {
    Mode currentMode = Y_EQUALS_X;
    std::string parsedEquation;
    inputEquation.erase(
        std::remove_if(inputEquation.begin(), inputEquation.end(), isspace),
        inputEquation.end());
    if (inputEquation.length() < 3) {
        return {currentMode, ""};
    }
    if (inputEquation[0] == 'y') {
        currentMode = Y_EQUALS_X;
        parsedEquation = inputEquation.substr(2);
    }
    else if (inputEquation[0] == 'x') {
        currentMode = X_EQUALS_Y;
        parsedEquation = inputEquation.substr(2);
    }
    else {
        currentMode = Y_EQUALS_X;
        parsedEquation = inputEquation;
    }

    return {currentMode, parsedEquation};
}
void generateWave(const std::string& s,Mode currentMode) {
    double mathX{0},mathY{0};
    te_parser parser;
    parser.set_variables_and_functions({{"x",&mathX},{"y",&mathY}});
    if (currentMode == Y_EQUALS_X) {
        int prevScreenX = 0;
        int prevScreenY = centerY;
        for (int screenX = 0 ;screenX < SCREEN_WIDTH;screenX++) {
            mathX = (screenX-centerX)/scale;
            mathY = parser.evaluate(s);
            int screenY = centerY - (mathY*scale);
            if (screenX > 0) {
                SDL_RenderDrawLine(app.renderer, prevScreenX, prevScreenY, screenX, screenY);
                // SDL_Delay(10);
            }
            prevScreenX = screenX;
            prevScreenY = screenY;
        }
    }else if (currentMode == X_EQUALS_Y) {
        int prevScreenX = centerX;
        int prevScreenY = 0;
        for (int screenY = 0 ;screenY < SCREEN_HEIGHT;screenY++) {
            mathY = (screenY-centerY)/scale;
            mathX = parser.evaluate(s);
            int screenX = centerX - (mathX*scale);
            if (screenX > 0) {
                SDL_RenderDrawLine(app.renderer, prevScreenX, prevScreenY, screenX, screenY);
                // SDL_Delay(100);
            }
            prevScreenX = screenX;
            prevScreenY = screenY;
        }

    }

}

[[noreturn]] int main(int argc, char *argv[]) {
    std::string s = "y = -x+2";
    std::string s2 = "x = y^2+3";
    auto [acex,equ] = parserInput(s);
    auto [acex1,equ1] = parserInput(s2);
    initSDL();
    while (true) {
        prepareScreen();
        mainLoop();
        graphLines();
        generateWave(equ,acex);
        generateWave(equ1,acex1);
        presentScreen();
        SDL_Delay(10);
    }
}
