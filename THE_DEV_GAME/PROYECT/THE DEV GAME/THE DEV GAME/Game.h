#pragma once
#include <string>
#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include <vector>

class Collider2D;
class TileComponent;

class Game {
private:
	sf::Event ev;
	sf::Clock deltaTimeclock;
	sf::RenderWindow window;

	float deltaTime;

	// Keyboard booleans
	bool keyPressed_Space;

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
	static std::vector<TileComponent*> Tiles;

	//Func
	void updateDeltaTime();

	void handleEvents();
	
	void updateNewPlayer();
	void updateCollision();

	static void AddTile(int id, int x, int y);

	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};

