#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Map::Map() {
}

Map::~Map() {
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	std::cout << "LOADING MAP.." << std::endl;
	char tile;
	std::string tileString;
	std::ifstream mapFile;
	mapFile.open(path);

	std::cout << "OPENED FILE MAP" << std::endl;

	int xCoord = 0;
	int yCoord = 0;
	
	if (mapFile) {
		std::string line{};
		size_t i{};

		while (getline(mapFile, line) && i < sizeY) //first read an entire line until all lines have been read
		{
			if (line.find(',') != std::string::npos)//then search for the ,
			{
				std::istringstream stream{ line.substr(line.find(',')) };

				while (stream)//while the stream is good
				{
					std::string temp_score;
					getline(stream, temp_score, ',');//peel off the scores from stream using the , delimiter
					//std::cout << temp_score << std::flush;
					if (temp_score != "") {
						GameState::AddTile(stoi(temp_score), xCoord * 50, yCoord * 50);

						// Set of elements based on the tileset data
						if (stoi(temp_score) == 7) {
							std::cout << "Placing point" << std::endl;
							GameState::PlacePoint(stoi(temp_score), xCoord * 50, yCoord * 50);
						}

						if (stoi(temp_score) == 6) {
							std::cout << "Placing Enemy" << std::endl;
							GameState::PlaceEnemy(stoi(temp_score), xCoord * 50, yCoord * 50);
						}

						//std::cout << xCoord << "." << yCoord << "=" << temp_score << std::endl;
						xCoord++;
						if (xCoord > sizeX) {
							xCoord = 0;
							yCoord++;
						}
					}
				}
			}
		}
	}

	//for (int y = 0; y < sizeY; y++) {
	//	for (int x = 0; x < sizeX; x++) {
	//		char TileId = '0';
	//		//std::cout << atoi(&tile) << std::endl;

	//		GameState::AddTile(0, x * 50, y * 50);

	//		//// Set of elements based on the tileset data
	//		//if (atoi(&tile) == 7) {
	//		//	std::cout << "Placing point" << std::endl;
	//		//	GameState::PlacePoint(atoi(&tile), x * 50, y * 50);
	//		//}

	//		//if (atoi(&tile) == 6) {
	//		//	std::cout << "Placing Enemy" << std::endl;
	//		//	GameState::PlaceEnemy(atoi(&tile), x * 50, y * 50);
	//		//}

	//		mapFile.ignore();
	//	}
	//}

	std::cout << "LOADING MAP SUCCESS!" << std::endl;
	mapFile.close();
}

void Map::UnloadMap() {

}
