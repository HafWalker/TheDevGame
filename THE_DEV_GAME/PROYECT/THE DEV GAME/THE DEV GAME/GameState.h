#pragma once
#include "State.h"

class TileComponent;
class Collider2D;

class GameState : public State
{
private:
	sf::Event ev;

	void initVariables();

	// Keyboard booleans
	bool keyPressed_Space;
	bool isPlayerJumping;
	bool inPlayerAttacking;

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	static std::vector<Collider2D*> colliders;
	static std::vector<TileComponent*> Tiles;
	static void AddTile(int id, int x, int y);

	//Functions
	void endState();
	void updateKeybinds(const float& st);

	void updatePlayerInput();
	void updateCollision();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};