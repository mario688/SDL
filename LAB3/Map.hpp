

#include "Game.hpp"

class Map {

public:

	Map();
	~Map();

	void LoadMap(int tab[20][25]);

	void DrawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* air;

	int map[20][25];



};