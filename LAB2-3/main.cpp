#include "Game.hpp"

Game* game = nullptr;
int main(int, char**)
{
    game = new Game();
    game->init("Gra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}





















