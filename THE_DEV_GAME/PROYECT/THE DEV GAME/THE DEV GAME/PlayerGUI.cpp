#include "stdafx.h"
#include "PlayerGUI.h"

PlayerGUI::PlayerGUI(sf::RenderWindow* window, sf::View* view) {
	this->initFonts();
	this->window = window;
	this->view = view;
}

PlayerGUI::~PlayerGUI() {
	delete this->playerHealthText;
	delete this->playerScoreText;
}

void PlayerGUI::init() {
	this->playerHealthText = new UIText(50, 50, 20, &this->font, "HEALT: 000");
	this->playerScoreText = new UIText(this->window->getSize().x - 100, 50, 20, &this->font, "SCORE: 000");
}

void PlayerGUI::initFonts() {
	if (!this->font.loadFromFile("../Assets/Fonts/rainyhearts/rainyhearts.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void PlayerGUI::update() {
	this->playerHealthText->SetText("SALUD: " + std::to_string(this->healtAmount));
	this->playerScoreText->SetText("SCORE: " + std::to_string(this->scoreAmount));
}

void PlayerGUI::render(sf::RenderTarget* target) {
	this->playerHealthText->SetPositionToView(this->view);
	this->playerScoreText->SetPositionToView(this->view);

	this->playerHealthText->render(target);
	this->playerScoreText->render(target);
}

void PlayerGUI::SetHealt(int value) {
	this->healtAmount = value;
}

void PlayerGUI::SetScore(int value) {
	this->scoreAmount = value;
}
