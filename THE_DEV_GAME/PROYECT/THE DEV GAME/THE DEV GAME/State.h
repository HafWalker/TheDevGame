#pragma once
#include"stdafx.h"
#include <vector>
#include <stack>
#include <map>

class State
{
private:

protected:
	sf::RenderWindow* window;
	std::vector<sf::Texture> Textures;
	bool quit;
public:
	State();
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState();

	virtual void updateKeybinds(const float& dt);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = nullptr);
};