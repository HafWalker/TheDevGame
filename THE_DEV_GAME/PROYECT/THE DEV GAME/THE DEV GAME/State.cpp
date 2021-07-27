#include "stdafx.h"
#include "State.h"

State::State() {

}

State::State(sf::RenderWindow* window) {
	this->window = window;
	this->quit = false;
}

State::~State() {

}

const bool& State::getQuit() const {
	return this->quit;
}

void State::checkForQuit() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->quit = true;
	}
}

void State::endState() {

}

void State::updateKeybinds(const float& dt) {

}

void State::update(const float& dt) {

}

void State::render(sf::RenderTarget* target) {

}
