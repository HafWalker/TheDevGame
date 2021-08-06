#pragma once

class PlayerGUI {
private:
	sf::RenderWindow* window;
	sf::View* view;

	sf::Font font;

	int healtAmount = 100;
	int scoreAmount = 0;

public:
	UIText* playerHealthText;
	UIText* playerScoreText;

	PlayerGUI(sf::RenderWindow* window, sf::View* view);
	~PlayerGUI();

	void init();
	void initFonts();
	void update();
	void render(sf::RenderTarget* target);

	void SetHealt(int value);
	void SetScore(int value);
};