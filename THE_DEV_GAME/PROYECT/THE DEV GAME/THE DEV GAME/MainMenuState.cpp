#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window) {
	this->window = window;
	this->quit = false;
}

MainMenuState::~MainMenuState() {

}

const bool& MainMenuState::getQuit() const {
	return this->quit;
}

void MainMenuState::checkForQuit() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->quit = true;
	}
}

void MainMenuState::endState() {

}

void MainMenuState::updateKeybinds(const float& dt) {

}

void MainMenuState::update(const float& dt) {

}

void MainMenuState::render(sf::RenderTarget* target) {

}
