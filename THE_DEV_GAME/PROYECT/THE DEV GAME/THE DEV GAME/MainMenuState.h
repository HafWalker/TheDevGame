#pragma once
#include "State.h"
#include "Button.h"
#include "InputField.h"

class MainMenuState : public State {
private:
	sf::RectangleShape background;
	sf::Font font;

	sf::Event ev;

	UIText* titleText;
	UIText* nameInputText;
	InputField* playerInputField;
	bool isKeyPressed;

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
	MainMenuState(sf::RenderWindow* window, sf::View* view, HighScore* highscore, std::stack<State*>* states);
	virtual ~MainMenuState();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState();

	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

