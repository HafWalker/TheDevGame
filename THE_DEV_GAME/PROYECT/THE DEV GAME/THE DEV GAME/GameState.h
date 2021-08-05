#pragma once
#include "State.h"
#include "UIText.h"
#include "PauseMenu.h"

class TileComponent;
class Collider2D;
class PointComponent;
class EnemyComponent;

class GameState : public State {
private:
	sf::Event ev;

	// UI
	sf::Font font;
	UIText* textScore;

	int scoreValue = 0;

	// PauseMenu

	PauseMenu* pauseMenu;

	// Functions
	void initVariables();
	void initFonts();

	// Keyboard booleans
	bool keyPressed_Space;
	bool isPlayerJumping;
	bool inPlayerAttacking;

	bool isGamePaused = false;
	bool isPausePressed = false;

	//Hacks
	int enemysDirection = 1;

public:
	GameState(sf::RenderWindow* window, sf::View* view, HighScore* highscore, std::stack<State*>* states);
	virtual ~GameState();

	static std::vector<Collider2D*> colliders;
	static std::vector<TileComponent*> Tiles;
	static std::vector<PointComponent*> Points;
	static std::vector<EnemyComponent*> Enemies;

	static void AddTile(int id, int x, int y);
	static void PlacePoint(int id, int x, int y);
	static void PlaceEnemy(int id, int x, int y);

	//Functions
	void endState();
	void updateKeybinds(const float& st);

	void updatePlayerInput();
	void updateCollision();
	void updateEnemys(const float& dt);
	void updateMapAnimations(const float& dt);
	void updateView(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

	void ClearMap();
};