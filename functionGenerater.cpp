//
// Created by darkrai on 12/30/25.
//

#include "functionGenerater.h"
#include "lib/tinyexpr.h"

FunctionGenerator::FunctionGenerator(Display& disp)
    : display(disp), running(true) {
}

std::tuple<Mode, std::string> FunctionGenerator::parseInput(std::string inputEquation) {
    Mode currentMode = Y_EQUATION;
    std::string parsedEquation;
    inputEquation.erase(std::remove_if(inputEquation.begin(), inputEquation.end(), isspace),inputEquation.end());

    if (inputEquation.length() < 3) {
        std::cerr <<"Equation length must be greater than 3"<<inputEquation<<std::endl;
        return {currentMode,""};
    }

    if (inputEquation[0] == 'y' || inputEquation[0] == 'Y' || inputEquation[1] == '=') {
        currentMode = Y_EQUATION;
        parsedEquation = inputEquation.substr(2);
    }else if (inputEquation[0] == 'x' || inputEquation[0] == 'X' || inputEquation[1] == '=') {
        currentMode = X_EQUATION;
        parsedEquation = inputEquation.substr(2);
    }else {
        currentMode = Y_EQUATION;
        parsedEquation = inputEquation.substr(2);
    }
    std::cout<<"Parsed equation: "<<parsedEquation<<std::endl;
    return {currentMode,parsedEquation};
}

void FunctionGenerator::generateWave(const Equation& eq) {
    double mathX{0},mathY{0};

    SDL_Renderer* renderer = display.getRenderer();
    SDL_SetRenderDrawColor(renderer, eq.color.r, eq.color.g, eq.color.b, eq.color.a);

    te_parser parser;
    parser.set_variables_and_functions({{"x",&mathX}, {"y",&mathY}});
    std::cout<<eq.equation<<"\n";
    if (eq.mode == Y_EQUATION) {
        int prevScreenX = 0;
        int prevScreenY =  CENTER_Y;
        bool firstpoint = true;
        for (int screenX = 0; screenX < SCREEN_WIDTH; screenX++) {
            mathX = (screenX - CENTER_X)/SCALE;
            mathY = parser.evaluate(eq.equation);


            int screenY = CENTER_Y - static_cast<int>(mathX*SCALE);


//             std::cout<<screenX<<" "<<screenY<<std::endl;

            if (!firstpoint) {
                SDL_RenderDrawLine(renderer, prevScreenX, prevScreenY, screenX, screenY);
            }
            prevScreenX = screenX;
            prevScreenY = screenY;
            firstpoint = false;
        }
    }else if (eq.mode == X_EQUATION) {
        int prevScreenX = CENTER_X;
        int prevScreenY = 0;
        bool firstpoint = true;
        for (int screenY = 0; screenY < SCREEN_HEIGHT; screenY++) {
            mathY = (screenY - CENTER_Y)/SCALE;
            mathX = parser.evaluate(eq.equation);

            // std::cout<<mathX<<" "<<mathY<<std::endl;

            int screenX = CENTER_X - static_cast<int>(mathX*SCALE);


            if (!firstpoint) {
                SDL_RenderDrawLine(renderer, prevScreenX, screenY, screenX, screenY);
            }
            prevScreenX = screenX;
            prevScreenY = screenY;
            firstpoint = false;
        }
    }
}

void FunctionGenerator::addEquation(const std::string& equation,SDL_Color color) {
    auto [parserMode, parserExp] = parseInput(equation);
    if (!parserExp.empty()) {
        equations.emplace_back(parserExp, parserMode, color);
        std::cout << "Add equation: "<<equations.size()<<":"<<parserExp<<" (Mode : "<<(parserMode == Y_EQUATION ? "Y" : "X") << ") parsed Equation: "<<parserExp<<std::endl;
    }else {
        std::cerr<<"Failed to add equation: "<<equation<<std::endl;
    }
}

void FunctionGenerator::removeEquation(size_t idx) {
    if (idx < equations.size()) {
        std::cout<<"Removing  Equation: "<<idx+1<<std::endl;
        equations.erase(equations.begin()+idx);
    }else {
        std::cerr<<"Failed to remove equation: "<<idx<<std::endl;
    }
}

void FunctionGenerator::clearEquations() {
    equations.clear();
    std::cout<<"Clear equations: "<<equations.size()<<std::endl;
}

void FunctionGenerator::run() {
    SDL_Event event;
    running = true;
    std::cout<<"Starting function generator with "<<equations.size()<<" equations"<<std::endl;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        display.prepareScreen();
        display.graphLines();


        for (const auto& equation : equations) {
            generateWave(equation);
        }
        display.prepareScreen();
        SDL_Delay(16);
    }
}

void FunctionGenerator::stop() {
    running = false;
    std::cout << "Stopping function generator" << std::endl;
}