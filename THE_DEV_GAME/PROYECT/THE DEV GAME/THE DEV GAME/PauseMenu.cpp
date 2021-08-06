#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, sf::View* view) {
	this->initFonts();
	this->window = window;
	this->view = view;
}

PauseMenu::~PauseMenu() {
	delete this->titleText;
	delete this->btn_Continue;
	delete this->btn_exit;
}

void PauseMenu::init() {
	background.setFillColor(sf::Color(0,0,0,100));
	background.setSize(this->view->getSize());

	float screenCenter = this->window->getSize().x * .5f - 75;
	this->titleText = new UIText(screenCenter + 75, 50, 50, &this->font, "PAUSE MENU!");
	//this->titleText->SetTextBackground(40.f, 5.f, sf::Color().Black, sf::Color().White, 2.f);

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

void PauseMenu::initFonts() {
	if (!this->font.loadFromFile("../Assets/Fonts/rainyhearts/rainyhearts.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void PauseMenu::update() {

	if (this->btn_Continue->isPressed()) {
		std::cout << "Pressed CONTINUE" << std::endl;
	}

	if (this->btn_exit->isPressed()) {
		std::cout << "Pressed EXIT" << std::endl;
	}
}

void PauseMenu::updatePauseMenuButtons(sf::Vector2f mousePositionView) {
	this->btn_Continue->update(mousePositionView);
	this->btn_exit->update(mousePositionView);
}

void PauseMenu::render(sf::RenderTarget* target) {

	sf::Vector2f inViewPosition = sf::Vector2f(
		(view->getCenter().x - view->getSize().x / 2),
		(view->getCenter().y - view->getSize().y / 2)
	);

	this->background.setPosition(inViewPosition);

	this->btn_Continue->SetPositionToView(this->view);
	this->btn_exit->SetPositionToView(this->view);
	this->titleText->SetPositionToView(this->view);

	this->window->draw(this->background);
	this->titleText->render(target);
	this->btn_Continue->render(target);
	this->btn_exit->render(target);
}