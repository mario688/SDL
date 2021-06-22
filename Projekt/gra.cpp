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
bool win = false;
bool menu = true;
SDL_Texture* LoadTexture(std::string file);

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Texture* playerTexture = NULL;
double angle = 0;

SDL_Texture* kladka = NULL;
SDL_Texture* meta = NULL;
SDL_Texture* kula = NULL;
SDL_Texture* menuBackground = NULL;
SDL_Texture* tlo = NULL;
SDL_Texture* playerJumpTexture = NULL;
SDL_Texture* currentTexture = NULL;
SDL_Texture* fallDown = NULL;
SDL_Texture* winBackground = NULL;
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

class Player
{
public:
    SDL_Rect Body;
    Player();
    float getYPos();
    void handleEvent(SDL_Event& e);
    float offSet;
    float xPos;
    float yPos;
    float xSpeed;
    float ySpeed;
    bool jump;
    float speed;
    float gravity;
    void move(SDL_Rect walls[10], SDL_Rect finish, SDL_Rect kulki[3]);
};
Player::Player()
{
    offSet = 0;
    xPos = 0;
    yPos = 600;
    jump = false;
    xSpeed = 0;
    speed = 1;
    gravity = 0.9;
    Body.w = 32;
    Body.h = 64;
}

float Player::getYPos() {
    return yPos;
}
bool canJump;
int oldPos;
void Player::move(SDL_Rect* walls, SDL_Rect finish, SDL_Rect* kulki)
{
    for (int i = 0; i < 3; i++) {
        if (checkCollision(Body, kulki[i]) != 7) {
            cout << "AUĆ!!" << endl;
            xPos = 0;
            yPos = 600;

        }

    }

    // cout << yPos << endl;
    offSet = getYPos();
    //xPos += xSpeed;
    if (checkCollision(Body, finish) == 3) {
        cout << "wygrales!!!" << endl;
        win = true;

    }
    else if (checkCollision(Body, finish) != 7)
    {
        xPos -= xSpeed;
        yPos -= xSpeed;
    }
    if (jump) {
        currentTexture = playerJumpTexture;
        for (int i = 0; i < 10; i++) {
            if ((checkCollision(Body, walls[i]) == 3 || yPos + Body.h > SCREEN_HEIGHT)) {
                canJump = true;
                oldPos = yPos;

            }
            if ((checkCollision(Body, walls[i]) == 6))
            {
               
                jump = false;
            }

        }

        if (canJump) {

            if (checkCollision(Body, walls[0]) != 6
                && checkCollision(Body, walls[1]) != 6
                && checkCollision(Body, walls[2]) != 6
                && checkCollision(Body, walls[3]) != 6
                && checkCollision(Body, walls[4]) != 6
                && checkCollision(Body, walls[5]) != 6
                && checkCollision(Body, walls[6]) != 6
                && checkCollision(Body, walls[7]) != 6
                && checkCollision(Body, walls[8]) != 6
                && checkCollision(Body, walls[9]) != 6

                ) {
                offSet -= 2.5;
                if (oldPos > yPos + 150) {
                    //cout << "Przekroczono limit wysokosci" << endl;
                    jump = false;
                    canJump = false;
                }
            }
            // cout << "offSet = " << offSet << " yPos = " << yPos << " oldPos = " << oldPos << endl;;
        }

        yPos = offSet;
    }
    else
        currentTexture = playerTexture;

    xPos += xSpeed;
    Body.x = xPos;
    Body.y = yPos;



    if (checkCollision(Body, walls[0]) != 3
        && checkCollision(Body, walls[1]) != 3
        && checkCollision(Body, walls[2]) != 3
        && checkCollision(Body, walls[3]) != 3
        && checkCollision(Body, walls[4]) != 3
        && checkCollision(Body, walls[5]) != 3
        && checkCollision(Body, walls[6]) != 3
        && checkCollision(Body, walls[7]) != 3
        && checkCollision(Body, walls[8]) != 3
        && checkCollision(Body, walls[9]) != 3 &&
        (yPos + Body.h < SCREEN_HEIGHT))
    {

        yPos += gravity;
        if (!jump) {
            currentTexture = fallDown;
        }
        
    }


    for (int i = 0; i < 10; i++) {
        if (checkCollision(Body, walls[i]) == 4)
        {
            xPos -= xSpeed;
        }

    }
    for (int i = 0; i < 10; i++) {
        if (checkCollision(Body, walls[i]) == 5)
        {
            xPos -= xSpeed;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (checkCollision(Body, walls[i]) == 6)
        {
            
            xPos += xSpeed;
        }
    }



    if (xPos < 0 || xPos + Body.w > SCREEN_WIDTH)
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
void Player::handleEvent(SDL_Event& e)
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
        case SDLK_SPACE:
            win = false;
            menu = false;
            break;
        case SDLK_ESCAPE:
            close();
            break;
        }

    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        
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
    bool doPrzodu = true;
    Player player;
    SDL_Rect screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect obstacle[3];
    SDL_Rect floors[10];
    SDL_Rect finish;
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        menuBackground = LoadTexture("menuBackground.png");
        winBackground = LoadTexture("winBackground.png");
        tlo = LoadTexture("background.png");
        kladka = LoadTexture("loaded.png");
        playerTexture = LoadTexture("player.png");
        playerJumpTexture = LoadTexture("jumpedPlayer.png");
        fallDown = LoadTexture("fallDown.png");
        meta = LoadTexture("meta.png");
        kula = LoadTexture("kulka.png");
        currentTexture = playerTexture;
        for (int i = 0; i < 10; i++) {
            floors[i].w = 130 - i * 10;
            floors[i].h = 30;
        }
        for (int x = 0; x < 3; x++) {
            obstacle[x].w = 30;
            obstacle[x].h = 60;
        }

        obstacle[0].x = 300;
        obstacle[0].y = 300;
        obstacle[1].x = 600;
        obstacle[1].y = 300;
        obstacle[2].x = 770;
        obstacle[2].y = 300;

        finish.w = 100;
        finish.h = 32;
        finish.x = 850;
        finish.y = 240;
        floors[0].x = 300;
        floors[0].y = 640;
        floors[1].x = 200;
        floors[1].y = 500;
        floors[2].x = 100;
        floors[2].y = 400;
        floors[2].w = 10;
        floors[3].x = 200;
        floors[3].y = 340;
        floors[4].x = 450;
        floors[4].y = 340;
        floors[5].x = 590;
        floors[5].y = 240;

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
                player.handleEvent(e);
            }


            player.move(floors, finish, obstacle);

            //Clear screen



            SDL_RenderClear(gRenderer);


            for (int i = 0; i < 3; i++) {
                if (obstacle[i].y > 400) {
                    doPrzodu = false;
                }
                else if (obstacle[i].y <= 0) {
                    doPrzodu = true;
                }

                if (doPrzodu) {
                    obstacle[i].y += 1;

                }
                else
                    obstacle[i].y -= 1;
            }


            //player.x = Time() / 5;
            if (menu) {
                SDL_RenderCopy(gRenderer, menuBackground, NULL, NULL);
            }else if(!win && !menu ) 
            {

                SDL_RenderCopy(gRenderer, tlo, NULL, NULL);
               
                for (int i = 0; i < 10; i++) {
                    SDL_RenderCopy(gRenderer, kladka, &screenRect, &floors[i]);
                }
                for (int i = 0; i < 3; i++) {
                    SDL_RenderCopy(gRenderer, kula, &screenRect, &obstacle[i]);
                }
                SDL_RenderCopy(gRenderer, meta, &screenRect, &finish);

                //render textury
                SDL_RenderCopyEx(gRenderer, currentTexture, NULL, &player.Body, angle, NULL, flip);

            }
            else {
                
                SDL_RenderCopy(gRenderer, winBackground, NULL, NULL);
            }
           

            //Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
