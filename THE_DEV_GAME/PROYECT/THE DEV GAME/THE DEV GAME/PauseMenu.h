#pragma once
#include "Button.h"

class PauseMenu {
private:
	sf::RenderWindow* window;
	sf::View* view;

	sf::RectangleShape background;
	sf::Font font;

public:
	PauseMenu(sf::RenderWindow* window, sf::View* view);
	~PauseMenu();
	
	Button* btn_Continue;
	Button* btn_exit;

	void init();
	void initFonts();
	void update();
	void updatePauseMenuButtons(sf::Vector2f mousePositionView);
	void render(sf::RenderTarget* target);
};

