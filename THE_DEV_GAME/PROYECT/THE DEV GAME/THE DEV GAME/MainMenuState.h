#pragma once
#include "State.h"
#include "Button.h"

class MainMenuState : public State {
private:
	sf::RectangleShape background;
	sf::Font font;

	Button* gamestate_button;
	Button* gamestate_exit;
	Button* gamestate_credits;

	// Functions
	void initVariables();
	void initFonts();

protected:
	std::vector<sf::Texture> Textures;
	bool quit;
public:
	MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState();

	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

