#include "Game.hpp"
#include <chrono>
#include <iostream>
#include "Vectors.hpp"
#include <thread>
#include "GameObject.hpp"
using namespace std::chrono;
using namespace std;
using namespace tp::operators;
Game* game = nullptr;
GameObject* bullet;
int main(int, char**)
{

    
    /*array<double, 2> bullet_p = { 0,100 };
    array<double, 2> bullet_v = { 10,-4 };
    array<double, 2> bullet_a = { 0,10 };*/
    
    milliseconds dt(15);
    steady_clock::time_point current_time = steady_clock::now(); // remember current time
    game = new Game();
    bullet = new GameObject("textury/postacie/player.png", 0, 0, 64, 64);
    game->init("Gra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    while (game->running()) {
       
        game->handleEvents();
        game->update();
        game->render();
       
 
       
        this_thread::sleep_until(current_time = current_time + dt);
    }
    game->clean();
    return 0;
}





















