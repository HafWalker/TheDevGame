#pragma once
#include <string>
#include "stdafx.h"
#include "TileMap.h"
#include "State.h"
#include <vector>

#include "GameState.h"
#include "MainMenuState.h"
#include "HighScore.h"

//class Collider2D;
//class TileComponent;

class Game {
private:
	sf::Event ev;

	// Scores
	HighScore* highscoreManager;

	sf::RenderWindow* window;
	sf::View* view;

	sf::Clock dtClock;
	float dt;

	void initVariables();
	void initView();
	void initWindow();

	//STATES

	std::stack<State*> states;
	void initStates();

public:

	Game();
	virtual ~Game();
	
	//static std::vector<Collider2D*> colliders;
	//static std::vector<TileComponent*> Tiles;

	//Func
	void updateDeltaTime();

	void handleEvents();

	void update();
	void render();
	void run();
};