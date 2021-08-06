#include "stdafx.h"
#include "EndOfLevel.h"

EndOfLevel::EndOfLevel(sf::RenderWindow* window, sf::View* view) {
	this->initFonts();
	this->window = window;
	this->view = view;
}

EndOfLevel::~EndOfLevel() {
	delete this->titleText;
	delete this->playerScore;
	delete this->btn_Continue;
	delete this->btn_exit;
}

void EndOfLevel::init() {
	background.setFillColor(sf::Color(0, 0, 0, 100));
	background.setSize(this->view->getSize());

	float screenCenter = this->window->getSize().x * .5f - 75;
	this->titleText = new UIText(screenCenter + 75, 50, 50, &this->font, "END LEVEL!");
	//this->titleText->SetTextBackground(40.f, 5.f, sf::Color().Black, sf::Color().White, 2.f);

	this->playerScore = new UIText(screenCenter + 75, 400, 50, &this->font, "Score: ");

	this->btn_Continue = new Button(screenCenter, 200, 150, 50,
		&this->font, "Continue",
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green);

	this->btn_exit = new Button(screenCenter, 300, 150, 50,
		&this->font, "Exit",
		sf::Color::Blue,
		sf::Color::Red,
		sf::Color::Green);
}

void EndOfLevel::initFonts() {
	if (!this->font.loadFromFile("../Assets/Fonts/rainyhearts/rainyhearts.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void EndOfLevel::update() {

	if (this->btn_Continue->isPressed()) {
		std::cout << "Pressed CONTINUE" << std::endl;
	}

	if (this->btn_exit->isPressed()) {
		std::cout << "Pressed EXIT" << std::endl;
	}
}

void EndOfLevel::updatePauseMenuButtons(sf::Vector2f mousePositionView) {
	this->btn_Continue->update(mousePositionView);
	this->btn_exit->update(mousePositionView);
}

void EndOfLevel::SetPlayerScoreToShow(string score) {
	this->playerScore->SetText("Score: " + score);
}

void EndOfLevel::render(sf::RenderTarget* target) {

	sf::Vector2f inViewPosition = sf::Vector2f(
		(view->getCenter().x - view->getSize().x / 2),
		(view->getCenter().y - view->getSize().y / 2)
	);

	this->background.setPosition(inViewPosition);

	//this->btn_Continue->SetMousePositionToView(this->view);
	this->btn_exit->SetMousePositionToView(this->view);
	this->titleText->SetMousePositionToView(this->view);
	this->playerScore->SetMousePositionToView(this->view);

	this->window->draw(this->background);
	this->titleText->render(target);
	this->playerScore->render(target);
	this->btn_Continue->render(target);
	this->btn_exit->render(target);
}