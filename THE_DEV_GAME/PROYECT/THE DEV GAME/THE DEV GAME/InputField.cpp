#include "stdafx.h"
#include "InputField.h"

InputField::InputField(float x, float y, int characterSize, sf::Font* textFont, std::string label) {
	this->text.setPosition(sf::Vector2f(x, y));
	this->font = textFont;
	this->text.setFont(*this->font);
	this->text.setString(label);
	this->text.setCharacterSize(characterSize);

	this->characterSize = characterSize;
}

InputField::~InputField() {
}

void InputField::update(sf::RenderWindow* window, sf::Event ev) {
	while (window->pollEvent(ev)) {
		if (ev.type == sf::Event::TextEntered) {
			std::cout << ev.text.unicode << std::endl;
			if (ev.text.unicode == '\b') {
				if (this->playerInput.getSize() > 0) {
					this->playerInput.erase(this->playerInput.getSize() - 1, 1);
					this->text.setString(this->playerInput);
				}
			}
			else if (ev.text.unicode == 27) {
				//this->endState();
			}
			else {
				this->playerInput += ev.text.unicode;
				this->text.setString(this->playerInput);
			}
		}
	}
}

void InputField::render(sf::RenderTarget* target) {
	target->draw(this->text);
}
