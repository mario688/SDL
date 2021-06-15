#include <iostream>
#include "Game.hpp"

#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "Vectors.hpp"
#include <array>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <vector>
//SDL_Texture* playerTexture;
//SDL_Rect srcR, destR;
GameObject* player;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Map* map;
using namespace std::chrono;
using namespace std;
using namespace tp::operators;
Game::Game()
{}
Game::~Game()
{}



void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flag = 0;
	if (fullscreen) {
		flag = SDL_WINDOW_FULLSCREEN;
	}
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Render created" << std::endl;
		}
		isRunning = true;
		

		

	}
	else {
		isRunning = false;
	}
	/*
	SDL_Surface* tempSurface = IMG_Load("player.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	*/
	//playerTexture = TextureManager::LoadTexture("player.png", renderer);
	player = new GameObject("textury/postacie/player.png", 0, 0,64,64);

	
	map = new Map();
}

void Game::handleEvents()
{
	//Keyboard::update();

	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
	default:
		break;
	}

	if (Game::event.type == SDL_KEYDOWN) {
		switch (Game::event.key.keysym.sym) {
		case SDLK_w:
			std::cout << "W" << std::endl;
			player->move(0);
			break;
		case SDLK_s:
			std::cout << "s" << std::endl;
			player->move(1);
			break;
		case SDLK_a:
			std::cout << "a" << std::endl;
			player->move(2);
			break;
		case SDLK_d:
			std::cout << "d" << std::endl;
			player->move(3);
			break;
		case SDLK_SPACE:
			std::cout << "SPACe" << std::endl;
			
			break;
		default:
			break;
		}

	}

}
void Game::update()
{	
	
	player->Update();
	
	

}
//tu bêd¹ dodawne rzeczy do renderu
void Game::render()
{

	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	
	

	//SDL_RenderCopy(renderer, playerTexture, NULL,&destR);
	SDL_RenderPresent(renderer);

}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Cleaned" << std::endl;
}