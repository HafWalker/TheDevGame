#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables() {
	float screenCenter = this->window->getSize().x * .5f - 75;
	this->initFonts();

	this->titleText = new UIText(screenCenter - 75, 50, 50, &this->font, "THE DEV GAME!");
	this->titleText->SetTextBackground(40.f,5.f,sf::Color().Black, sf::Color().White, 2.f);

	this->playerInputField = new InputField(screenCenter, 500, 50, &this->font, "PlayerX");
	this->playerInputField->playerInput = "PlayerX";

	this->nameInputText = new UIText(screenCenter - 175, 500, 50, &this->font, "Nombre: ");

	this->gamestate_button = new Button(screenCenter, 200, 150, 50,
		&this->font, "New Game",
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green);

	this->gamestate_exit = new Button(screenCenter, 300, 150, 50,
		&this->font, "Exit",
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green);

	this->gamestate_credits = new Button(screenCenter, 400, 150, 50,
		&this->font, "Scores",
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
	delete this->titleText;
	delete this->gamestate_button;
	delete this->gamestate_exit;
	delete this->gamestate_credits;
	delete this->playerInputField;
	delete this->nameInputText;
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
	this->checkForQuit();
}

void MainMenuState::update(const float& dt) {
	this->view->setCenter(this->window->getSize().x/2, this->window->getSize().y / 2);
	this->updateKeybinds(dt);
	this->updateMousePositions();
	this->playerInputField->update(this->window, ev);

	this->gamestate_button->update(this->mousePositionView);
	this->gamestate_exit->update(this->mousePositionView);
	this->gamestate_credits->update(this->mousePositionView);

	if (this->gamestate_button->isPressed()) {
		this->highscore->AddScore(this->playerInputField->playerInput, 0);
		this->highscore->currentPlayer = std::string(this->playerInputField->playerInput);
		std::cout << this->highscore->currentPlayer << std::endl;
		std::cout << "Pressed GAME" << std::endl;
		this->states->push(new GameState(this->window, this->view, this->highscore, this->states));
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
	this->window->setView(*view);
	this->titleText->render(target);
	this->gamestate_button->render(target);
	this->gamestate_exit->render(target);
	this->gamestate_credits->render(target);
	this->nameInputText->render(target);
	this->playerInputField->render(target);
}
