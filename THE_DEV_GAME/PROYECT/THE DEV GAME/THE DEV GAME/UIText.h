#pragma once
#include "stdafx.h"

class UIText {
private:
	sf::Font* font;
	sf::Text text;
public:
	UIText(float x, float y, int characterSize, sf::Font* textFont, std::string label);
	~UIText();
	void update(std::string value);
	void render(sf::RenderTarget* target);
	void SetPosition(float x, float y) {
		this->text.setPosition(x, y);
	}
};

