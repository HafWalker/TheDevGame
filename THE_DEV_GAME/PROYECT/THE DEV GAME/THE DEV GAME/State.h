#pragma once
#include"stdafx.h"
#include <vector>
#include <stack>
#include <map>
#include "HighScore.h"

class State
{
private:

protected:
	std::stack<State*>* states;
	sf::RenderWindow* window;
	sf::View* view;
	HighScore* highscore;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;

	bool quit;
public:
	State();
	State(sf::RenderWindow* window, sf::View* view, HighScore* highscore, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();
	virtual void QuitState();

	virtual void endState();

	virtual void updateKeybinds(const float& dt);
	virtual void updateMousePositions();
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target = nullptr);
};