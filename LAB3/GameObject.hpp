#pragma once
#include "Game.hpp"

class GameObject {

public:
	GameObject(const char* texturka, int x, int y,int w,int h);
	~GameObject();


	void Update();
	void Render();
	void Shoot();
	void move(int d);
	
private:
	int xpos;
	int ypos;
	int height;
	int width;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;


};