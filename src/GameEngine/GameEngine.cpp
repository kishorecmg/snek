#include "GameEngine.hpp"

GameEngine::GameEngine(const int SCREEN_WIDTH, const int SCREEN_HEIGHT) 
    : window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer),
    process_running(true), snake()
{
    SDL_Init(SDL_INIT_VIDEO);
    window.reset(SDL_CreateWindow("Snek", 20, 20, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));

    snake.set_renderer(renderer.get());
}

GameEngine::~GameEngine() 
{
    SDL_Quit();
}

void GameEngine::run()
{
    while(process_running)
    {
        /*while(SDL_PollEvent(&evente))
        {
            if(evente.type == SDL_QUIT)
            {
                process_running = false;
            }
            else if(evente.type == SDL_KEYDOWN)
            {
                rect1.y = rect.y;
                rect1.x = rect.x;
                switch (evente.key.keysym.sym)
                {  
                case SDLK_UP:
                    rect.y -= rect.y != 0 ? 20 : 0;
                    break;
                case SDLK_DOWN:
                    rect.y += rect.y != 360-20 ? 20 : 0;
                    break;
                case SDLK_LEFT:
                    rect.x -= rect.x != 0 ? 20 : 0;
                    break;
                case SDLK_RIGHT:
                    rect.x += rect.x != 640-20 ? 20 : 0;
                    break;
                default:
                    break;
                }
            }
        }*/

        SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.get());
        
        process_running = snake.update();
        
        /*SDL_SetRenderDrawColor(renderer.get(), 0x00, 0xFF, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer.get(), &rect);
        
        SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0x00, 0xFF, 0xFF);
        SDL_RenderFillRect(renderer.get(), &rect1);*/
        
        SDL_RenderPresent(renderer.get());
    }
}