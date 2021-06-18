/*
    Autor:Mario
    Źródła:
    - https://www.youtube.com/channel/UCStD9dM0fAPxyJqrWWwFHPQ,
    - https://lazyfoo.net/tutorials/SDL/,
    - https://wiki.libsdl.org/
*/
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();
Uint32 startTime;

int checkCollision(SDL_Rect a, SDL_Rect b);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

SDL_Texture* LoadTexture(std::string file);

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Texture* texture = NULL;
double angle = 0;
SDL_Texture* kladka = NULL;

SDL_RendererFlip flip = SDL_FLIP_NONE;
using namespace std;
string direction = "left";

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    //Create window
    gWindow = SDL_CreateWindow("Hellow World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    //Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    int imgFlaga = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlaga) & imgFlaga))
    {
        printf("SDL_IMAGE nie zostal zainicjalizowany %s\n ", IMG_GetError());
        return false;
    }
    startTime = SDL_GetTicks();
    return success;
}
Uint32 Time() {
    return SDL_GetTicks() - startTime;
}
SDL_Texture* LoadTexture(std::string file)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(file.c_str());

    if (loadedSurface == NULL)
    {
        printf("teksturka niezaladowana: %s\n", file.c_str(), IMG_GetError());
    }
    else
    {

        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
            printf("nie stworzono textury %s\n", file.c_str(), SDL_GetError());

        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
void close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

class Ship
{
public:
    SDL_Rect ShipHull;
    Ship();
    float getYPos();
    void handleEvent(SDL_Event& e);
    int offSet;
    float xPos;
    float yPos;
    float xSpeed;
    float ySpeed;
    bool jump;
    float speed;
    float gravity;
    void move(SDL_Rect walls[10]);
};
Ship::Ship()
{
    offSet = 0;
    xPos = 100;
    yPos = 100;
    jump = false;
    xSpeed = 0;
    speed = 0.3;
    gravity = 0.8;
    ShipHull.w = 32;
    ShipHull.h = 64;
}

float Ship::getYPos() {
    return yPos;
}
bool canJump;
int oldPos;
void Ship::move(SDL_Rect* walls)
{
    

    // cout << yPos << endl;
    offSet = getYPos();
    //xPos += xSpeed;
    if (jump) {

        for (int i = 0; i < 10; i++) {
            if ((checkCollision(ShipHull, walls[i]) == 3 || yPos + ShipHull.h > SCREEN_HEIGHT)) {
                canJump = true;
                oldPos = yPos;
            }
        }
        
        if (canJump) {
            
            if (checkCollision(ShipHull, walls[0]) != 6
                && checkCollision(ShipHull, walls[1]) != 6
                && checkCollision(ShipHull, walls[2]) != 6
                && checkCollision(ShipHull, walls[3]) != 6
                && checkCollision(ShipHull, walls[4]) != 6
                && checkCollision(ShipHull, walls[5]) != 6
                && checkCollision(ShipHull, walls[6]) != 6
                && checkCollision(ShipHull, walls[7]) != 6
                && checkCollision(ShipHull, walls[8]) != 6
                && checkCollision(ShipHull, walls[9]) != 6
                
                ) {
                offSet -= 1;
                if (oldPos > yPos + 150) {
                    //cout << "Przekroczono limit wysokosci" << endl;
                    jump = false;
                }
            }
            // cout << "offSet = " << offSet << " yPos = " << yPos << " oldPos = " << oldPos << endl;;
        }

        yPos = offSet;
    }
    xPos += xSpeed;
    ShipHull.x = xPos;
    ShipHull.y = yPos;
    
   
        
        if (checkCollision(ShipHull, walls[0]) != 3
            && checkCollision(ShipHull, walls[1]) != 3 
            && checkCollision(ShipHull, walls[2]) != 3 
            && checkCollision(ShipHull, walls[3]) != 3
            && checkCollision(ShipHull, walls[4]) != 3 
            && checkCollision(ShipHull, walls[5]) != 3
            && checkCollision(ShipHull, walls[6]) != 3
            && checkCollision(ShipHull, walls[7]) != 3
            && checkCollision(ShipHull, walls[8]) != 3
            && checkCollision(ShipHull, walls[9]) != 3 &&
            (yPos + ShipHull.h < SCREEN_HEIGHT))
        {

            yPos += gravity;
        }
       
        for (int i = 0; i < 10; i++) {
            if (checkCollision(ShipHull, walls[i]) == 4)
            {
                xPos -= xSpeed;
            }
        }
        for (int i = 0; i < 10; i++) {
            if (checkCollision(ShipHull, walls[i]) == 5)
            {
                xPos -= xSpeed;
            }
        }
        
        for (int i = 0; i < 10; i++) {
            if (checkCollision(ShipHull, walls[i]) == 6)
            {

                xPos += xSpeed;
            }
        }
        
        
    
    if (xPos < 0 || xPos + ShipHull.w > SCREEN_WIDTH)
    {
        xPos -= xSpeed;
    }

    //cout << "ShipHull.x = " << ShipHull.x << " " << "ShipHull.y = " << ShipHull.x << endl;
}
int checkCollision(SDL_Rect a, SDL_Rect b)
{
    

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if ((bottomA + 1 == topB - 1 || bottomA + 1 == topB - 1) && rightA > leftB && rightB > leftA)
    {
        //cout << "JEst kolizja z góry " << i<<endl;
        return 3;
    }
    else if ((leftA == rightB || leftA == rightB) && (topB < bottomA && topA < bottomB))
    {
        //cout << "JEst kolizja z lewej od gracza " << i << endl;
        return 4;
    }
    else if ((rightA == leftB || rightA == leftB) && (topB < bottomA && topA < bottomB))
    {
        //cout << "JEst kolizja z prawej od gracza " << i << endl;
        return 5;
    }
    else if ((topA + 1 == bottomB - 1 || topA - 1 == bottomB + 1) && rightA > leftB && rightB > leftA)
    {
        //cout << "JEst kolizja z dolu " << i << endl;
        return 6;
    }

    return 7;
}
void Ship::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {

        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            jump = true;


            direction = "up";
            break;
        case SDLK_DOWN:
            // cos zrobic

            direction = "down";
            break;
        case SDLK_LEFT:
            direction = "left";

            xSpeed -= speed;
            break;
        case SDLK_RIGHT:

            direction = "right";

            xSpeed += speed;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:

            jump = false;

            break;
        case SDLK_DOWN:

            // cos dodac
            break;
        case SDLK_LEFT:

            xSpeed += speed;
            break;
        case SDLK_RIGHT:

            xSpeed -= speed;
            break;
        }
    }
}

int main(int argc, char* args[])
{
    
    Ship ship;
    SDL_Rect screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
 
    SDL_Rect floors[10];
  
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {   int numberOfFlor =   -1;
        kladka = LoadTexture("loaded.png");
        texture = LoadTexture("player.png");
        for (int i = 0; i < 10; i++) {
            floors[i].w = 130 - i*10;
            floors[i].h = 30;
        }
       

        floors[0].x = 300;
        floors[0].y = 740;
        floors[1].x = 200;
        floors[1].y = 640;
        floors[2].x = 130;
        floors[2].w = 10;
        floors[2].y = 440;
        floors[3].x = 400;
        floors[3].y = 340;
        floors[4].x = 600;
        floors[4].y = 340;
       
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;
      
        //While application is running
        while (!quit)
        {
            
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                ship.handleEvent(e);
            }
            
         
            ship.move(floors);

            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 42, 123, 33, 255);

            SDL_RenderClear(gRenderer);

            //player.x = Time() / 5;
            SDL_SetRenderDrawColor(gRenderer, 42, 255, 255, 255);
            //SDL_RenderCopy(gRenderer, kladka, &screenRect, &obstacle);
            for (int i = 0; i < 10; i++) {
                SDL_RenderCopy(gRenderer, kladka, &screenRect, &floors[i]);
            }
           
            //render textury
            SDL_RenderCopyEx(gRenderer, texture, NULL, &ship.ShipHull, angle, NULL, flip);

            //Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
