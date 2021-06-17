
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool checkCollision(SDL_Rect a, SDL_Rect b);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;


SDL_Texture* LoadTexture(std::string file);

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Texture* texture = NULL;



using namespace std;

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

	if (!(IMG_Init(imgFlaga) & imgFlaga)) {
		printf("SDL_IMAGE nie zostal zainicjalizowany %s\n ", IMG_GetError());
		return false;
	}




	return success;
}

SDL_Texture* LoadTexture(std::string file) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(file.c_str());

	if (loadedSurface == NULL) {
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

class Ship {
public:
	SDL_Rect ShipHull;
	Ship();
	void handleEvent(SDL_Event& e);
	float xPos;
	float yPos;
	float xSpeed;
	float ySpeed;
	float speed;
	void move(SDL_Rect przeszkoda);

};
Ship::Ship() {
	xPos = 0;
	yPos = 0;
	ySpeed = 0;
	xSpeed = 0;
	speed = 0.3;
	ShipHull.w = 100;
	ShipHull.h = 100;

}
void Ship::move(SDL_Rect przeszkoda) {
	

	xPos += xSpeed;
	yPos += ySpeed;
	ShipHull.x = xPos;
	ShipHull.y = yPos;

	if (checkCollision(przeszkoda, ShipHull)) {
		xPos -= xSpeed;
		cout << "kolizja";
	}


	if (checkCollision(przeszkoda, ShipHull)) {
		yPos -= ySpeed;
		cout << "kolizja";
	}
	cout << "ShipHull.x = " << ShipHull.x << " " << "ShipHull.y = " << ShipHull.x << endl;
}
void Ship::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{

		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			
			ySpeed -= speed;
			break;
		case SDLK_DOWN:
			
			ySpeed += speed;
			break;
		case SDLK_LEFT:
			
			xSpeed -= speed;
			break;
		case SDLK_RIGHT:
			
			xSpeed += speed;
			break;
		}
	}else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			
			ySpeed += speed;
			break;
		case SDLK_DOWN:
			
			ySpeed -= speed;
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
bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

   
    return true;
}
int main(int argc, char* args[])
{

	Ship ship;
	SDL_Rect screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect obstacle = { 300,100,100,100 };
	
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		texture = LoadTexture("dot.png");
		if (texture == NULL) {
			printf("failed to load obrazek");
			return -1;
		}

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				ship.handleEvent(e);
			}

			
			ship.move(obstacle);
		
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 42, 123, 33, 255);
			
			SDL_RenderClear(gRenderer);




			//player.x = Time() / 5;
			SDL_SetRenderDrawColor(gRenderer, 42, 255, 255, 255);
			SDL_RenderFillRect(gRenderer, &obstacle);
			//render textury
			SDL_RenderCopy(gRenderer, texture, &screenRect, &ship.ShipHull);








			//Update screen
			SDL_RenderPresent(gRenderer);
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}
