#include "stdafx.h"
#include "GameState.h"
#include "Map.h"

Manager manager;

std::vector<Collider2D*> GameState::colliders;
std::vector<TileComponent*> GameState::Tiles;

auto& newPlayer(manager.addEntity());

void GameState::initVariables() {
	std::cout << "Init Variables" << std::endl;
	keyPressed_Space = false;
	isPlayerJumping = false;
	inPlayerAttacking = false;

	Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level1_16x12.map", 16,12);
	//Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level2_32x21.map", 32, 21);
	//Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level1_TEST.map", 16, 12);

	newPlayer.addComponent<Transform>(100, 350, 100, 55, 1);
	newPlayer.addComponent<SpriteComponent>("D:/THE_DEV_GAME/PROYECT/Sprites/Animation/Player_Full_SpriteSheet.png");
	newPlayer.addComponent<AnimatorComponent>(128, 128);
	newPlayer.addComponent<Collider2D>("Player");
	newPlayer.addComponent<Rigidbody2D>();
}

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states) {
	this->window = window;
	initVariables();
}

GameState::~GameState() {
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
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
		CollisionInfo collisionInfo;
		collisionInfo = Collision::AABB(newPlayer.getComponent<Collider2D>(), *cc);
		if (collisionInfo.isColliding) {
			if (collisionInfo.tag != "Player") {
				//std::cout << "Disp" << collisionInfo.displacement * 0.2f << std::endl;
				//newPlayer.getComponent<Transform>().DetectCollision(collisionInfo.displacement);
				newPlayer.getComponent<Rigidbody2D>().move(collisionInfo.displacement * 0.02f);
			}

			if (collisionInfo.tag == "Wall" && isPlayerJumping && newPlayer.getComponent<AnimatorComponent>().getAnimationEnd(ANIMATION_STATES::FALLING)) {
				isPlayerJumping = false;
				newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::IDLE);
			}
		}
	}
}

void GameState::update(const float& dt) {
	this->updateKeybinds(dt);
	this->updatePlayerInput();
	this->updateCollision();
	manager.update();
}

void GameState::render(sf::RenderTarget* target) {

	// Render
	for (auto cc : Tiles) {
		this->window->draw(cc->entity->getComponent<SpriteComponent>().GetSprite());
		if (cc->entity->hasComponents<Collider2D>()) {
			//this->window->draw(cc->entity->getComponent<Collider2D>().collider);
		}
	}

	this->window->draw(newPlayer.getComponent<SpriteComponent>().GetSprite());
	//TextureManager::Draw(newPlayer.getComponent<SpriteComponent>().GetSprite());

	// COLLISION DEBUG
		//this->window.draw(newPlayer.getComponent<Collider2D>().collider);
	//

	// SPRITES DEBUG
		//this->window.draw(newPlayer.getComponent<SpriteComponent>().GetDebugSpriteIntRect());
	//
}