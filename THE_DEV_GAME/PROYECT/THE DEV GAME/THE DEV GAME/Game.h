#pragma once
#include <string>
#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;
	TileMap tileMap;

	void initVariables();
	void initWindow();
	void initTileMap();
	void initPlayer();

public:
	Game();
	virtual ~Game();

	//Func
	void updatePlayer();
	void updateCollision();

	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;

	// Debug
	void log(std::string str);
};

