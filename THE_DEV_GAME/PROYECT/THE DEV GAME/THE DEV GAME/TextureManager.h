#pragma once
#include "Game.h"

class TextureManager {
private:
	//static sf::RenderWindow* window;
public:
	static void SetRenderTarget(sf::RenderWindow* win);
	static sf::Texture* LoadTexture(const char* fileName);
	static void Draw(sf::Sprite& sprite);
};

