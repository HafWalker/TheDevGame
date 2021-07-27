#include "stdafx.h"
#include "Map.h"
#include <fstream>

Map::Map() {
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	std::cout << "LOADING MAP" << std::endl;
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			GameState::AddTile(atoi(&tile), x * 50, y * 50);
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::UnloadMap() {

}
