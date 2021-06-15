#include "GameObject.hpp"
#include <chrono>
#include "Vectors.hpp"
#include <iostream>
#include "TextureManager.hpp"
#include <thread>
using namespace std::chrono;
using namespace std;
using namespace tp::operators;
GameObject::GameObject(const char* texturka, int x, int y,int w,int h)
{

	objTexture = TextureManager::LoadTexture(texturka);
	xpos = x;
	ypos = y;
	height = h;
	width = w;
}
void GameObject::Update()
{
	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}


void GameObject::move(int d) {
	switch (d) {
	case 0:
		ypos -= 10;
		break;
	case 1:
		ypos += 10;
		break;
	case 2:
		xpos -= 10;
		break;
	case 3:
		xpos += 10;
		break;

	}
}


void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
