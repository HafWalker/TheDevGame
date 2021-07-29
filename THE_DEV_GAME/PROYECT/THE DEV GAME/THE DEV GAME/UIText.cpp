#include "UIText.h"
#include "stdafx.h"

UIText::UIText(float x, float y, int characterSize, sf::Font* textFont, std::string label) {
	this->text.setPosition(sf::Vector2f(x, y));
	this->font = textFont;
	this->text.setFont(*this->font);
	this->text.setString(label);
	this->text.setCharacterSize(characterSize);
}

UIText::~UIText() {
}

void UIText::update(std::string value) {
	this->text.setString(value);
}

void UIText::render(sf::RenderTarget* target) {
	target->draw(this->text);
}
