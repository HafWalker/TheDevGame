#include "stdafx.h"
#include "TextureManager.h"

sf::Texture* TextureManager::LoadTexture(const char* filename) {
	sf::Texture* result = new sf::Texture();
	result->loadFromFile(filename);
	if (!result) {
		std::cout << "ERROR: CANT LOAD TEXTURESHEET" << "\n";
	}
	return result;
}
