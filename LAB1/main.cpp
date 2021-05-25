#include <SDL.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <vector>
#include <array>

 // check for errors
#define errcheck(e)                   \
  {                                   \
    if (e)                            \
    {                                 \
      cout << SDL_GetError() << endl; \
      SDL_Quit();                     \
      return -1;                      \
    }                                 \
  }

    int main(int, char**)
{
    using namespace std;
    using namespace std::chrono;
    int width = 640;
    int height = 480;
    //inicjalizacja video do grafiki
    errcheck(SDL_Init(SDL_INIT_VIDEO) != 0);

    //tworzenie okna
    shared_ptr<SDL_Window> window(SDL_CreateWindow(
        "My Next Superawesome Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN),
        [=](auto w) { SDL_DestroyWindow(w); });

    errcheck(window == nullptr);

    shared_ptr<SDL_Renderer> renderer(SDL_CreateRenderer(
        window.get(), -1, SDL_RENDERER_ACCELERATED), // SDL_RENDERER_PRESENTVSYNC
        [=](auto r) { SDL_DestroyRenderer(r); });
    errcheck(renderer == nullptr);

    std::array<int, 4> position = { 10,10 };
    int r= 125, g= 125, b = 125;
    int w = 10, h = 10;
    int mouseX = 10, mouseY = 10;
    
    //auto dt = 15ms;
    milliseconds dt(15);

    steady_clock::time_point current_time = steady_clock::now(); // remember current time
    for (bool game_active = true; game_active;)
    {
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        { // check if there are some events

            switch (event.type)
            {
            case SDL_QUIT:
                game_active = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) game_active = false;
               if (event.key.keysym.sym == SDLK_SPACE) 
                {
                   cout << "clear background"<<endl;
                   SDL_SetRenderDrawColor(renderer.get(), 255, 255,255, 255);
                  SDL_RenderClear(renderer.get());
               } 
               if (event.key.keysym.sym == SDLK_w)
               {
                   h += 10;
                   w += 10;
                   cout << "H= " << h << " " << "W= " << w << endl;
               }
               if (event.key.keysym.sym == SDLK_s)
               {
                   h -= 10;
                   w -= 10;
                   cout << "H= " << h << " " << "W= " << w << endl;
               }
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    
                    
                    cout <<"LEFTMOUSEBUTTONCLICKED"<<endl;
                  
                    
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    cout << "RIGHTMOUSEBUTTONCLICKED" << endl;
                }
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.button.x;
                mouseY = event.button.y;
                cout << "x = " << mouseX << endl;
                cout << "y = " << mouseY << endl;
            }
            

        }
        
        auto kstate = SDL_GetKeyboardState(NULL);
        if (kstate[SDL_SCANCODE_LEFT]) {
            position[0] -= 1;
            b++;
        }
        if (kstate[SDL_SCANCODE_RIGHT]) {
            position[0] += 1;
            b++;
        }
        if (kstate[SDL_SCANCODE_DOWN]) {
            position[1] += 1;
            g++;
        }
        if (kstate[SDL_SCANCODE_UP]) {
            position[1] -= 1;
            r++;
        }
       
        
        SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
        //SDL_RenderClear(renderer.get());

        SDL_SetRenderDrawColor(renderer.get(), r, g, b, 255);

        
        SDL_Rect rect = { position[0], position[1], w,h };
        SDL_Rect rectangleMouse = { mouseX, mouseY, w,h };
        
        SDL_RenderDrawRect(renderer.get(), &rectangleMouse);
        SDL_RenderDrawRect(renderer.get(), &rect);

        SDL_RenderPresent(renderer.get()); // draw frame to screen
        
        this_thread::sleep_until(current_time = current_time + dt);
    }
    SDL_Quit();
    return 0;
}





















