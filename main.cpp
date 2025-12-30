#include "functionGenerater.h"
int main(int argc, char* argv[]) {
    try {
        Display display;
        display.initSDL();
        FunctionGenerator function_generator(display);
        function_generator.addEquation("y = sin(x)*10");
        function_generator.addEquation("y = sqrt(23^2 - x^2)",{23,234,122,232});
        function_generator.run();
    } catch (std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}