#include "stdafx.h"
#include "Game.h"
#include "Map.h"

Manager manager;

//How To Make Games #13 Fix to events

std::vector<Collider2D*> Game::colliders;
std::vector<TileComponent*> Game::Tiles;

auto& newPlayer(manager.addEntity());

void Game::initVariables() {
	std::cout << "Init Variables" << std::endl;
	keyPressed_A = false;
	keyPressed_D = false;
	keyPressed_W = false;
	keyPressed_S = false;

	Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level1_16x12.map", 16,12);
	//Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level2_32x21.map", 32, 21);
	//Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level1_TEST.map", 16, 12);

	newPlayer.addComponent<Transform>(100, 350, 100, 55, 1);
	newPlayer.addComponent<SpriteComponent>("D:/THE_DEV_GAME/PROYECT/Sprites/StaticSprite.png");
	newPlayer.addComponent<Collider2D>("Player");
	newPlayer.addComponent<Rigidbody2D>();
}

void Game::initWindow() {
	std::cout << "Init Window" << std::endl;
	this->window.create(sf::VideoMode(800, 600), "The Dev Game", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
	TextureManager::SetRenderTarget(&this->window);
}

void Game::initTileMap() {
	std::cout << "Init TileMap (Empty)" << std::endl;
}

void Game::initPlayer() {
	std::cout << "Init Native Player" << std::endl;
	this->player = new Player();
}

Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initPlayer();
}

Game::~Game() {
	delete this->player;
}

void Game::updateDeltaTime() {
	this->deltaTime = this->deltaTimeclock.restart().asSeconds();
}

void Game::handleEvents() {
	window.pollEvent(ev);
	switch (ev.type) {
	case sf::Event::Closed:
		// Commented to prevent a weird bug (Open and instan close the game)
		//this->window.close();
		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape) {
			this->window.close();
		}
		break;
	default:
		break;
	}
}

void Game::updateNewPlayer() {
	/// SFML ORTIVA TRATA LOS PRESS Y RELEASE DE FORMA DIFERENTE (PRESS ONCE / RELEAS CONTINUOUS)
	if (ev.type == sf::Event::KeyPressed) {
		if(ev.key.code == sf::Keyboard::A && !keyPressed_A){
			keyPressed_A = true;
			newPlayer.getComponent<Transform>().velocity.Add(Vector2D(-1.f, 0.f));
		}
		else if (ev.key.code == sf::Keyboard::D && !keyPressed_D) {
			keyPressed_D = true;
			newPlayer.getComponent<Transform>().velocity.Add(Vector2D(1.f, 0.f));
		}

		if (ev.key.code == sf::Keyboard::W && !keyPressed_W) {
			keyPressed_W = true;
			newPlayer.getComponent<Transform>().velocity.Add(Vector2D(0.f, -1.f));
		}
		else if (ev.key.code == sf::Keyboard::S && !keyPressed_S) {
			keyPressed_S = true;
			newPlayer.getComponent<Transform>().velocity.Add(Vector2D(0.f, 1.f));
		}

		if (ev.key.code == sf::Keyboard::Space) {
			keyPressed_W = true;
			newPlayer.getComponent<Transform>().Translate(Vector2D(0.f, -3.f));
		}
	}
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::A && keyPressed_A) {
			keyPressed_A = false;
			newPlayer.getComponent<Transform>().velocity.Substract(Vector2D(-1.f, 0.f));
		}
		else if (ev.key.code == sf::Keyboard::D && keyPressed_D) {
			keyPressed_D = false;
			newPlayer.getComponent<Transform>().velocity.Substract(Vector2D(1.f, 0.f));
		}

		if (ev.key.code == sf::Keyboard::W && keyPressed_W) {
			keyPressed_W = false;
			newPlayer.getComponent<Transform>().velocity.Substract(Vector2D(0.f, -1.f));
		}
		else if (ev.key.code == sf::Keyboard::S && keyPressed_S) {
			keyPressed_S = false;
			newPlayer.getComponent<Transform>().velocity.Substract(Vector2D(0.f, 1.f));
		}
	}
}

void Game::updatePlayer() {
	this->player->update();
}

void Game::updateCollision() {
	std::cout << "DEBUG - - - - - " << std::endl;
	std::cout << "Velocity:" << newPlayer.getComponent<Transform>().velocity << std::endl;
	std::cout << "Suppress:" << newPlayer.getComponent<Transform>().vectorCollision << std::endl;
	for (auto cc : colliders) {
		CollisionInfo collisionInfo;
		collisionInfo = Collision::AABB(newPlayer.getComponent<Collider2D>(), *cc);
		if (collisionInfo.isColliding) {
			if (collisionInfo.tag != "Player") {
				//std::cout << collisionInfo.diff << std::endl;
				//newPlayer.getComponent<Transform>().DetectCollision(collisionInfo.displacement);
				newPlayer.getComponent<Transform>().position += collisionInfo.displacement;
			}
		}
	}
}

void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 50, 50, id);
}

void Game::update() {
	this->handleEvents();
	this->updatePlayer();
	this->updateNewPlayer();
	this->updateCollision();
	manager.update();
}

void Game::renderPlayer() {
	this->player->render(this->window);
}

void Game::render() {
	this->window.clear();

	// Render
	this->renderPlayer();

	for (auto cc : Tiles) {
		this->window.draw(cc->entity->getComponent<SpriteComponent>().GetSprite());
		if (cc->entity->hasComponents<Collider2D>()) {
			this->window.draw(cc->entity->getComponent<Collider2D>().collider);
		}
	}

	this->window.draw(newPlayer.getComponent<SpriteComponent>().GetSprite());
	//TextureManager::Draw(newPlayer.getComponent<SpriteComponent>().GetSprite());

	// COLLISION DEBUG
		this->window.draw(newPlayer.getComponent<Collider2D>().collider);
	//

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const {
	return this->window;
}