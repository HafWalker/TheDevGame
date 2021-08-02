#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables() {
	float screenCenter = this->window->getSize().x * .5f - 75;
	this->initFonts();
	this->gamestate_button = new Button(screenCenter, 100, 150, 50,
		&this->font, "New Game",
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green);

	this->gamestate_exit = new Button(screenCenter, 200, 150, 50,
		&this->font, "Exit",
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green);

	this->gamestate_credits = new Button(screenCenter, 300, 150, 50,
		&this->font, "Credits",
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green);
}

void MainMenuState::initFonts() {
	if (!this->font.loadFromFile("D:/THE_DEV_GAME/PROYECT/Fonts/rainyhearts/rainyhearts.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

MainMenuState::MainMenuState(sf::RenderWindow* window, sf::View* view, HighScore* highscore, std::stack<State*>* states) : State(window, view, highscore, states) {
	this->window = window;
	this->view = view;
	this->highscore = highscore;
	this->initVariables();
	this->quit = false;
}

MainMenuState::~MainMenuState() {
	delete this->gamestate_button;
	delete this->gamestate_exit;
	delete this->gamestate_credits;
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
	this->quit = true; // Not used Rn
	this->window->close();
}

void MainMenuState::updateKeybinds(const float& dt) {

}

void MainMenuState::update(const float& dt) {
	this->updateMousePositions();

	this->gamestate_button->update(this->mousePositionView);
	this->gamestate_exit->update(this->mousePositionView);
	this->gamestate_credits->update(this->mousePositionView);

	if (this->gamestate_button->isPressed()) {
		this->states->push(new GameState(this->window, this->view, this->highscore, this->states));
		std::cout << "Pressed GAME" << std::endl;
	}

	if (this->gamestate_exit->isPressed()) {
		this->endState();
		std::cout << "Pressed EXIT" << std::endl;
	}

	if (this->gamestate_credits->isPressed()) {
		std::cout << "Pressed CREDITS" << std::endl;
	}
}

void MainMenuState::render(sf::RenderTarget* target) {
	this->gamestate_button->render(target);
	this->gamestate_exit->render(target);
	this->gamestate_credits->render(target);
}
