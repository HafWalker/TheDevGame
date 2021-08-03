#pragma once
#include "stdafx.h"

class InputField {
private:
	sf::Font* font;
	int characterSize;
public:
	sf::Text text;
	sf::String playerInput;

	InputField(float x, float y, int characterSize, sf::Font* textFont, std::string label);
	~InputField();

	void update(sf::RenderWindow* window, sf::Event ev);
	void render(sf::RenderTarget* target);
};

