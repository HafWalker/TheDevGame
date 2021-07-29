#include "stdafx.h"
#include "GameState.h"
#include "Map.h"

Manager manager;

std::vector<Collider2D*> GameState::colliders;
std::vector<TileComponent*> GameState::Tiles;

auto& newPlayer(manager.addEntity());
auto& newPlayerAttackArea(manager.addEntity());

auto& newEnemy(manager.addEntity());
auto& newEnemyAttackArea(manager.addEntity());

auto& newPoint(manager.addEntity());

void GameState::initVariables() {
	std::cout << "Init Variables" << std::endl;
	keyPressed_Space = false;
	isPlayerJumping = false;
	inPlayerAttacking = false;

	this->initFonts();

	this->textScore = new UIText(55,55, 24, &this->font, "Score: 0");

	//Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level1_16x12.map", 16,12);
	Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level2_32x21.map", 32, 21);
	//Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level1_TEST.map", 16, 12);

	newPlayer.addComponent<Transform>(100, 350, 100, 55, 1);
	newPlayer.addComponent<SpriteComponent>("D:/THE_DEV_GAME/PROYECT/Sprites/Animation/Player_Full_SpriteSheet.png");
	newPlayer.addComponent<AnimatorComponent>(128, 128);
	newPlayer.addComponent<Collider2D>("Player",0.f,0.f);
	newPlayer.addComponent<Rigidbody2D>();

	//Animation settings for Player

	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ IDLE,2,48});
	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ MOVING_LEFT,3,15 });
	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ MOVING_RIGHT,3,15 });
	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ TAKE_DAMAGE,6,32 });
	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ ATTACK,4,31 });
	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ JUMPING,5,22 });
	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ FALLING,1,22 });
	newPlayer.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ DIE,0,73 });
	newPlayer.getComponent<AnimatorComponent>().setAnimationState(IDLE);

	newPlayerAttackArea.addComponent<Transform>(100, 350, 100, 55, 1);
	newPlayerAttackArea.addComponent<Collider2D>("PlayerHitArea", 50.f, 25.f, 50.f, 50.f);

	//newPlayer.getComponent<AnimatorComponent>().SetIdleAnimation(2, 48);

	newEnemy.addComponent<Transform>(300,450, 50, 55, 1);
	newEnemy.addComponent<SpriteComponent>("D:/THE_DEV_GAME/PROYECT/Sprites/Animation/spritesheet_enemy_full.png");
	newEnemy.addComponent<AnimatorComponent>(128, 128);
	newEnemy.addComponent<Collider2D>("Enemy", 0.f, 25.f);
	newEnemy.addComponent<Rigidbody2D>();
	newEnemy.addComponent<EnemyAI>(Vector2D(1.f, 0.f), 0.05f, 100.f, 500.f);

	newEnemy.getComponent<Rigidbody2D>().gravity = 0.f;
	newEnemy.getComponent<EnemyAI>().SetAttackTimer(7.f);

	//Animation settings for enemy

	newEnemy.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ IDLE,2,81 });
	newEnemy.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ ATTACK,1,81 });
	newEnemy.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ DIE,0,31 });
	newEnemy.getComponent<AnimatorComponent>().setAnimationState(IDLE);
	//newEnemy.getComponent<AnimatorComponent>().SetIdleAnimation(2, 81);

	// Point

	newPoint.addComponent<Transform>(300, 250, 50, 55, 1);
	newPoint.addComponent<SpriteComponent>("D:/THE_DEV_GAME/PROYECT/Sprites/Animation/spritesheet_point.png");
	newPoint.addComponent<AnimatorComponent>(128, 128);
	newPoint.addComponent<Collider2D>("Enemy", 0.f, 25.f);
	newPoint.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ IDLE,0,81 });
	newPoint.getComponent<AnimatorComponent>().setAnimationState(IDLE);
	
	// Init View Center
	this->view->setCenter(sf::Vector2f(newPlayer.getComponent<Transform>().position.x, newPlayer.getComponent<Transform>().position.y));
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("D:/THE_DEV_GAME/PROYECT/Fonts/rainyhearts/rainyhearts.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

GameState::GameState(sf::RenderWindow* window, sf::View* view, std::stack<State*>* states) : State(window, view, states) {
	this->window = window;
	this->view = view;
	initVariables();
}

GameState::~GameState() {
	delete this->textScore;
}

void GameState::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 50, 50, id);
}

void GameState::endState() {
	std::cout << "Ending game stuff" << std::endl;
}

void GameState::updateKeybinds(const float& st) {
	this->checkForQuit();
}

void GameState::updatePlayerInput() {
	this->window->pollEvent(ev);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !inPlayerAttacking) {
		newPlayer.getComponent<Rigidbody2D>().move(Vector2D(-0.1f, 0.f));
		if (!isPlayerJumping) {
			newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::MOVING_LEFT);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !inPlayerAttacking) {
		newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.1f, 0.f));
		if (!isPlayerJumping) {
			newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::MOVING_RIGHT);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, -0.1f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, 0.1f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !keyPressed_Space) {
		keyPressed_Space = true;
		isPlayerJumping = true;
		newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::FALLING);
		newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, -2.f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && !inPlayerAttacking) {
		inPlayerAttacking = true;
		newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::ATTACK);
		//newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, -2.f));
	}

	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::Space && keyPressed_Space) {
			keyPressed_Space = false;
		}

		if (ev.key.code == sf::Keyboard::J) {
			inPlayerAttacking = false;
		}

		if (ev.key.code == sf::Keyboard::A ||
			ev.key.code == sf::Keyboard::D) {
			newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::IDLE);
		}
		//TODO: Return to IDLE animation (ASDW)
	}

	//if (abs(newPlayer.getComponent<Transform>().velocity.x) < 0.5f && abs(newPlayer.getComponent<Transform>().velocity.y) < 0.5f) {
	//	isPlayerJumping = false;
	//	newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::IDLE);
	//}

	/// TESTING

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {

	}
}

void GameState::updateCollision() {
	for (auto cc : colliders) {
		// Player
		CollisionInfo collisionInfo;
		collisionInfo = Collision::AABB(newPlayer.getComponent<Collider2D>(), *cc);
		if (collisionInfo.isColliding) {
			if (collisionInfo.tag != "Player" &&
				collisionInfo.tag != "PlayerHitArea" &&
				collisionInfo.tag != "Enemy") {
				//std::cout << "Disp" << collisionInfo.displacement * 0.2f << std::endl;
				//newPlayer.getComponent<Transform>().DetectCollision(collisionInfo.displacement);
				newPlayer.getComponent<Rigidbody2D>().move(collisionInfo.displacement * 0.02f);
			}

			if (collisionInfo.tag == "Wall" && isPlayerJumping && newPlayer.getComponent<AnimatorComponent>().getAnimationEnd(ANIMATION_STATES::FALLING)) {
				isPlayerJumping = false;
				newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::IDLE);
			}
		}

		//Enemy
		collisionInfo = Collision::AABB(newEnemy.getComponent<Collider2D>(), *cc);
		if (collisionInfo.isColliding) {
			if (collisionInfo.tag == "PlayerHitArea" && inPlayerAttacking && newEnemy.getComponent<EnemyAI>().isAlive) {
				newEnemy.getComponent<AnimatorComponent>().setAnimationState(DIE);
				newEnemy.getComponent<EnemyAI>().TakeDamage();
			}
		}
	}
}

void GameState::update(const float& dt) {
	this->updateKeybinds(dt);
	this->updatePlayerInput();
	this->updateCollision();
	this->updateView(dt);

	newPlayer.getComponent<AnimatorComponent>().updateDeltaTime(dt);
	newEnemy.getComponent<AnimatorComponent>().updateDeltaTime(dt);
	newPoint.getComponent<AnimatorComponent>().updateDeltaTime(dt);

	newPlayerAttackArea.getComponent<Transform>().position = newPlayer.getComponent<Transform>().position;
	updateEnemys(dt);

	manager.update();
}

void GameState::updateEnemys(const float& dt) {
	newEnemy.getComponent<EnemyAI>().UpdateDeltaTime(dt);
	if (newEnemy.getComponent<EnemyAI>().GetAttackTrigger()) {
		newEnemy.getComponent<AnimatorComponent>().setAnimationState(ATTACK);
	}
}

void GameState::updateView(const float& dt) {
	sf::Vector2f playersPosition = sf::Vector2f(newPlayer.getComponent<Transform>().position.x, newPlayer.getComponent<Transform>().position.y);
	sf::Vector2f movement = playersPosition - this->view->getCenter();
	this->view->move(sf::Vector2f(movement * dt * 2.f));

	// Set the Score text in the top left of the view
	this->textScore->SetPosition(this->view->getCenter().x - (this->view->getSize().x/2), this->view->getCenter().y - (this->view->getSize().y / 2));
}

void GameState::render(sf::RenderTarget* target) {

	this->window->setView(*view);
	// Render
	for (auto cc : Tiles) {
		this->window->draw(cc->entity->getComponent<SpriteComponent>().GetSprite());
		if (cc->entity->hasComponents<Collider2D>()) {
			//this->window->draw(cc->entity->getComponent<Collider2D>().collider);
		}
	}

	this->window->draw(newEnemy.getComponent<SpriteComponent>().GetSprite());
	this->window->draw(newPlayer.getComponent<SpriteComponent>().GetSprite());
	this->window->draw(newPoint.getComponent<SpriteComponent>().GetSprite());

	//TextureManager::Draw(newPlayer.getComponent<SpriteComponent>().GetSprite());

	// COLLISION DEBUG
	//this->window->draw(newEnemy.getComponent<Collider2D>().collider);
	//this->window->draw(newPlayerAttackArea.getComponent<Collider2D>().collider);
	//this->window->draw(newPlayer.getComponent<Collider2D>().collider);
	//this->window->draw(newPoint.getComponent<Collider2D>().collider);
	//

	// SPRITES DEBUG
	//this->window->draw(newEnemy.getComponent<SpriteComponent>().GetDebugSpriteIntRect());
	//

	// UI - RENDER
	this->textScore->render(this->window);
}