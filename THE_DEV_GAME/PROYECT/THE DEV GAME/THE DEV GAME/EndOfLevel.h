#pragma once
#include "Button.h"

class EndOfLevel {
private:
	sf::RenderWindow* window;
	sf::View* view;

	UIText* titleText;
	UIText* playerScore;

	sf::RectangleShape background;
	sf::Font font;

public:
	EndOfLevel(sf::RenderWindow* window, sf::View* view);
	~EndOfLevel();

	Button* btn_Continue;
	Button* btn_exit;

	void init();
	void initFonts();
	void update();
	void updatePauseMenuButtons(sf::Vector2f mousePositionView);
	
	void SetPlayerScoreToShow(string score);

	void render(sf::RenderTarget* target);
};