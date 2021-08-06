#pragma once
#include "stdafx.h"

enum BUTTON_STATES {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button {
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	float startOffsetX = 0;
	float startOffsetY = 0;

public:
	Button(float x, float y, float w, float h, 
		sf::Font* buttonFont, std::string label,
		sf::Color idleButtonColor, 
		sf::Color hoverButtonColor, 
		sf::Color activeButtonColor);
	~Button();

	//Accesors
	const bool isPressed() const;

	//Function
	void update(const sf::Vector2f mousePosition);
	void render(sf::RenderTarget* target);

	void SetPositionToView(sf::View* view);
};

