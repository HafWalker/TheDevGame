#include "stdafx.h"
#include "UIText.h"

UIText::UIText(float x, float y, int characterSize, sf::Font* textFont, std::string label) {
	this->text.setPosition(sf::Vector2f(x, y));
	this->font = textFont;
	this->text.setFont(*this->font);
	this->text.setString(label);
	this->text.setCharacterSize(characterSize);

	this->characterSize = characterSize;
}

UIText::~UIText() {
}

void UIText::update(std::string value) {
	this->text.setString(value);
}

void UIText::render(sf::RenderTarget* target) {
	if (useBackground) {
		target->draw(this->background);
	}
	target->draw(this->text);
}

void UIText::SetText(std::string value) {
	this->text.setString(value);
}

void UIText::SetPosition(float x, float y) {
	this->text.setPosition(x, y);
}

void UIText::SetTextBackground(float borderX, float borderY, sf::Color baseColor, sf::Color outlineColor, float outlineWidth) {
	useBackground = true;
	backgroundRect = text.getLocalBounds();
	background.setPosition(text.getPosition().x - (borderX/2), text.getPosition().y + 7.5f);
	background.setSize(sf::Vector2f(backgroundRect.width + borderX, this->characterSize + borderY));
	background.setFillColor(baseColor);
	background.setOutlineColor(outlineColor);
	background.setOutlineThickness(outlineWidth);
}