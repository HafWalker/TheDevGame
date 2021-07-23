#pragma once
#include <string>
#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include <vector>

class Collider2D;

class Game {
private:
	sf::Event ev;
	sf::RenderWindow window;
	sf::Clock deltaTimeclock;
	float deltaTime;

	// Keyboard booleans
	bool keyPressed_A;
	bool keyPressed_D;
	bool keyPressed_W;
	bool keyPressed_S;

	Player* player;
	TileMap tileMap;

	void initVariables();
	void initWindow();
	void initTileMap();
	void initPlayer();

public:

	Game();
	virtual ~Game();
	
	static std::vector<Collider2D*> colliders;

	//Func
	void updateDeltaTime();

	void handleEvents();
	
	void updateNewPlayer();
	void updatePlayer();
	void updateCollision();

	static void AddTile(int id, int x, int y);

	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

