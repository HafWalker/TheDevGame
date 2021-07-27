#pragma once
#include "State.h"

class MainMenuState : public State {
private:

protected:
	sf::RenderWindow* window;
	std::vector<sf::Texture> Textures;
	bool quit;
public:
	MainMenuState(sf::RenderWindow* window);
	virtual ~MainMenuState();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState();

	void updateKeybinds(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

