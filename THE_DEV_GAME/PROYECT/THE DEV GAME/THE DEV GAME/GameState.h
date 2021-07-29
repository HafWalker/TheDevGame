#pragma once
#include "State.h"
#include "UIText.h"

class TileComponent;
class Collider2D;

class GameState : public State
{
private:
	sf::Event ev;

	// UI
	sf::Font font;
	UIText* textScore;

	// Functions
	void initVariables();
	void initFonts();

	// Keyboard booleans
	bool keyPressed_Space;
	bool isPlayerJumping;
	bool inPlayerAttacking;

	//Hacks
	int enemysDirection = 1;

public:
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	static std::vector<Collider2D*> colliders;
	static std::vector<TileComponent*> Tiles;
	static void AddTile(int id, int x, int y);

	//Functions
	void endState();
	void updateKeybinds(const float& st);

	void updatePlayerInput();
	void updateCollision();
	void updateEnemys(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};