#include "Map.hpp"
#include "TextureManager.hpp"

int lvl1[20][25] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0},
	{3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,2,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,2,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,2,2,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0},


};

Map::Map() {
	dirt = TextureManager::LoadTexture("textury/bloki/dirt.png");
	grass = TextureManager::LoadTexture("textury/bloki/grass.png");
	water = TextureManager::LoadTexture("textury/bloki/water.png");
	air = TextureManager::LoadTexture("textury/bloki/air.png");

	LoadMap(lvl1);
	src.x = 0;
	src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
}

void Map::LoadMap(int tab[20][25]) {

	for (int i = 0; i < 20; i++) {
		for (int x = 0; x < 25; x++) {
			map[i][x] = tab[i][x];
		}

	}

}



void Map::DrawMap() {

	int type = 0;
	for (int i = 0; i < 20; i++) {
		for (int x = 0; x < 25; x++) {

			type = map[i][x];

			dest.x = x * 32;
			dest.y = i * 32;

			switch (type) {
			case 0:
				TextureManager::Draw(air, src, dest);
				break;
			case 1:
				TextureManager::Draw(water, src, dest);
				break;
			case 2:
				TextureManager::Draw(dirt, src, dest);
				break;
			case 3:
				TextureManager::Draw(grass, src, dest);
				break;
			default:
				break;
			}

		}

	}
}