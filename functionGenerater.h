//
// Created by darkrai on 12/30/25.
//

#ifndef FUNCTION_GENERATOR_H
#define FUNCTION_GENERATOR_H

#include "display.h"
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cctype>
#include <cmath>
enum Mode {
    Y_EQUATION,
    X_EQUATION,
};

struct Equation {
    std::string equation;
    Mode mode;
    SDL_Color color;

    Equation(const std::string& equation, Mode mode, SDL_Color color = {255, 0, 0, 255})
        : equation(equation), mode(mode), color(color) {}
};

class FunctionGenerator {
private:
    Display& display;
    std::vector<Equation> equations;
    bool running;

    std::tuple<Mode, std::string> parseInput(std::string inputEquation);
    void generateWave(const Equation& eq);

public:
    explicit FunctionGenerator(Display& display);
    void addEquation(const std::string& equation, SDL_Color color = {255, 0, 0, 255});
    void clearEquations();
    void removeEquation(size_t index);
    void run();
    void stop();

    size_t getEquationCount() const { return equations.size(); }
};

#endif //FUNCTION_GENERATER_FUNCTIONGENERATER_H