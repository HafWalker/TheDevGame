#pragma once
#include "stdafx.h"

class UIText {
private:
	sf::Font* font;
	sf::Text text;
	sf::FloatRect backgroundRect;
	sf::RectangleShape background;
	int characterSize;
	bool useBackground = false;

	float startOffsetX = 0;
	float startOffsetY = 0;

public:
	UIText(float x, float y, int characterSize, sf::Font* textFont, std::string label);
	~UIText();
	void update(std::string value);
	void render(sf::RenderTarget* target);
	void SetText(std::string value);
	void SetPosition(float x, float y);
	void SetTextBackground(float borderX, float borderY, sf::Color baseColor, sf::Color outlineColor, float outlineWidth);
	void SetPositionToView(sf::View* view);
};

