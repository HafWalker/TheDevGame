#include "stdafx.h"
#include "State.h"

State::State() {

}

State::State(sf::RenderWindow* window, sf::View* view, HighScore* highscore, std::stack<State*>* states) {
	this->window = window;
	this->view = view;
	this->quit = false;
	this->highscore = highscore;
	this->states = states;
}

State::~State() {

}

const bool& State::getQuit() const {
	return this->quit;
}

void State::checkForQuit() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->view->setCenter(sf::Vector2f(this->window->getSize().x/2,this->window->getSize().y/2));
		this->quit = true;
	}
}

void State::endState() {
	
}

void State::updateKeybinds(const float& dt) {

}

void State::updateMousePositions() {
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::update(const float& dt) {

}

void State::render(sf::RenderTarget* target) {

}
