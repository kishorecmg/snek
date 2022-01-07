#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>

class Snakke
{
    private:
        std::vector<SDL_Rect> parts;
        SDL_Rect prey;

        SDL_Event evente;
        SDL_Renderer* renderer;

        uint32_t timer;

        enum Directions { UP, DOWN, LEFT, RIGHT } direction;

    public:
        Snakke();
        ~Snakke();

        void set_renderer(SDL_Renderer*);

        bool update();

        void reset_snake();
};