#include "./src/GameEngine/GameEngine.hpp"

int main(int argv, char** argc)
{
    GameEngine ge(640, 360);

    ge.run();

    return 0;
}