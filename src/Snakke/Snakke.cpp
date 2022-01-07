#include "./Snakke.hpp"

Snakke::Snakke()
    : parts({{100, 100, 20, 20}, {100, 80, 20, 20}, {100, 60, 20, 20}, {100, 40, 20, 20}}),
    prey({ 300, 300, 20, 20 }), direction(Directions::DOWN), timer(0)
{ }

Snakke::~Snakke() {  }

void Snakke::set_renderer(SDL_Renderer* p_renderer)
{
    renderer = p_renderer;
}

bool Snakke::update()
{    
    if(timer > 20)
    {
        timer = 0;
        for(int i = parts.size() - 1; i > 0; i--)
        {
            parts.at(i).x = parts.at(i - 1).x;
            parts.at(i).y = parts.at(i - 1).y;
        }
        // printf("%d %d ;", parts.at(0).x, parts.at(0).y);
        switch(direction)
        {
        case Directions::UP:
            parts.at(0).y -= 20;
            break;
        case Directions::DOWN:
            parts.at(0).y += 20;
            break;
        case Directions::LEFT:
            parts.at(0).x -= 20;
            break;
        case Directions::RIGHT:
            parts.at(0).x += 20;
            break;
        }
    }

    timer++;

    while (SDL_PollEvent(&evente))
    {
        if (evente.type == SDL_QUIT)
        {
            return false;
        }
        else if (evente.type == SDL_KEYDOWN)
        {
            switch (evente.key.keysym.sym)
            {
            case SDLK_UP:
                direction = direction != Directions::DOWN? Directions::UP : Directions::DOWN;
                break;
            case SDLK_DOWN:
                direction = direction != Directions::UP ? Directions::DOWN : Directions::UP;
                break;
            case SDLK_LEFT:
                direction = direction != Directions::RIGHT ? Directions::LEFT : Directions::RIGHT;
                break;
            case SDLK_RIGHT:
                direction = direction != Directions::LEFT ? Directions::RIGHT : Directions::LEFT;
                break;
            default:
                break;
            }
        }
    }

    if (parts.at(0).x < prey.x + prey.w && parts.at(0).x + parts.at(0).w > prey.x &&
        parts.at(0).y < prey.y + prey.h && parts.at(0).y + parts.at(0).h > prey.y)
    {
        parts.push_back({parts.at(parts.size()-1).x, parts.at(parts.size()-1).y, 20, 20});
        prey.x = rand() % 640;
        prey.y = rand() % 360;
    }
    
    if(parts.at(0).x < 0 || parts.at(0).x > 640 || parts.at(0).y < 0 || parts.at(0).y > 360)
    {
        Snakke::reset_snake();
    }

    for (int i = 1; i < parts.size() - 1; i++)
    {
        if (parts.at(0).x < parts.at(i).x + parts.at(i).w && parts.at(0).x + parts.at(0).w > parts.at(i).x &&
            parts.at(0).y < parts.at(i).y + parts.at(i).h && parts.at(0).y + parts.at(0).h > parts.at(i).y)
        {
            Snakke::reset_snake();
            break;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &prey);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRects(renderer, &parts.at(0), parts.size());

    return true;
}

void Snakke::reset_snake()
{
    parts.clear();
    parts = {{100, 100, 20, 20}, {100, 80, 20, 20}, {100, 60, 20, 20}, {100, 40, 20, 20}};
    prey = {300, 300, 20, 20};
    direction = Directions::DOWN;
    timer = 0;
}