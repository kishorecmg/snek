#include<memory>
#include <SDL2/SDL.h>
#include "../Snakke/Snakke.hpp"

class GameEngine
{
    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
        // SDL_Event evente;
        bool process_running;

        Snakke snake;
        // SDL_Rect rect, rect1;

    public:
        GameEngine(const int, const int); 
        ~GameEngine();

        void run();
};