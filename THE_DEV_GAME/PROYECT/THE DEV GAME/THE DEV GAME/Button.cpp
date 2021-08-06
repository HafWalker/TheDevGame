#include "stdafx.h"
#include "Button.h"

Button::Button(float x, float y, float w, float h,
	sf::Font* buttonFont, std::string label,
	sf::Color idleButtonColor,
	sf::Color hoverButtonColor,
	sf::Color activeButtonColor) 
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(w, h));
	this->font = buttonFont;
	this->text.setFont(*this->font);
	this->text.setString(label);
	this->shape.setFillColor(sf::Color::White);
	this->text.setCharacterSize(24);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width * .5f) - (this->text.getGlobalBounds().width * .5f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height * .5f) - (this->text.getGlobalBounds().height * .5f) - 10.f
	);

	this->idleColor = idleButtonColor;
	this->hoverColor = hoverButtonColor;
	this->activeColor = activeButtonColor;

	this->startOffsetX = x;
	this->startOffsetY = y;
}

Button::~Button() {

}

const bool Button::isPressed() const {
	if (this->buttonState == BTN_ACTIVE) {
		return true;
	}
	return false;
}

void Button::update(const sf::Vector2f mousePosition) {
	this->buttonState = BTN_IDLE;
	if (this->shape.getGlobalBounds().contains(mousePosition)) {
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Magenta);
		break;
	}
}

void Button::render(sf::RenderTarget* target) {
	target->draw(this->shape);
	target->draw(this->text);
}

void Button::SetPositionToView(sf::View* view) {
	sf::Vector2f inViewPosition = sf::Vector2f(
		startOffsetX + (view->getCenter().x - view->getSize().x / 2),
		startOffsetY + (view->getCenter().y - view->getSize().y / 2)
	);

	this->shape.setPosition(inViewPosition);

	this->text.setPosition(
		inViewPosition.x + (this->shape.getGlobalBounds().width * .5f) - (this->text.getGlobalBounds().width * .5f),
		inViewPosition.y + (this->shape.getGlobalBounds().height * .5f) - (this->text.getGlobalBounds().height * .5f) - 10.f
	);
}
