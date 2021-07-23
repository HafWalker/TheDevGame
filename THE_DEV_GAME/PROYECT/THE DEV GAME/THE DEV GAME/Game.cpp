#include "stdafx.h"
#include "Game.h"

Manager manager;

//How To Make Games #13 Fix to events

std::vector<Collider2D*> Game::colliders;

auto& newPlayer(manager.addEntity());
auto& Tile0(manager.addEntity());
auto& Tile1(manager.addEntity());
auto& Tile2(manager.addEntity());

void Game::initVariables() {
	std::cout << "Init Variables" << std::endl;
	keyPressed_A = false;
	keyPressed_D = false;
	keyPressed_W = false;
	keyPressed_S = false;

	Tile0.addComponent<TileComponent>(128, 128, 128, 128, 0);
	Tile0.addComponent<Collider2D>("Floor");
	
	Tile1.addComponent<TileComponent>(128+128, 128+128, 128, 128, 1);
	
	Tile2.addComponent<TileComponent>(128+128+128, 128+128+128, 128, 128, 2);
	Tile2.addComponent<Collider2D>("Box");

	newPlayer.addComponent<Transform>(0, 0, 128, 128, 1);
	newPlayer.addComponent<SpriteComponent>("D:/THE_DEV_GAME/PROYECT/Sprites/DefaultSprite.png");
	newPlayer.addComponent<Collider2D>("Player");
}

void Game::initWindow() {
	std::cout << "Init Window" << std::endl;
	this->window.create(sf::VideoMode(800, 600), "The Dev Game", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initTileMap() {
	std::cout << "Init TileMap (Empty)" << std::endl;
	//this->tileMap = new TileMap();
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
	// Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y) {
		this->player->resetVelocityY();
		this->player->setCanJump(true);
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
	}	// Collision Right of screen
	else if (this->player->getPosition().x + this->player->getGlobalBounds().width > this->window.getSize().x) {
		this->player->resetVelocityY();
		this->player->setPosition(
			this->window.getSize().x - this->player->getGlobalBounds().width,
			this->player->getPosition().y
		);
	}	// Collision Left of screen
	else if (this->player->getPosition().x + this->player->getGlobalBounds().width < 0.f + this->player->getGlobalBounds().width) {
		this->player->resetVelocityY();
		this->player->setPosition(
			0.f,
			this->player->getPosition().y
		);
	}

	// Collision with Tiles
	// Top Collision
	//if((this->player->getPosition().y + this->player->getGlobalBounds().height > )
}

void Game::update() {
	// Polling event
	/*while (this->window.pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed) {
			this->window.close();
		}
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) {
			this->window.close();
		}

		if (this->ev.type == sf::Event::KeyReleased &&
			(	this->ev.key.code == sf::Keyboard::A ||
				this->ev.key.code == sf::Keyboard::D ||
				this->ev.key.code == sf::Keyboard::W ||
				this->ev.key.code == sf::Keyboard::S 
			)) {
			this->player->resetAnimationTimer();
		}
	}*/

	this->handleEvents();
	this->updatePlayer();
	this->updateNewPlayer();
	this->updateCollision();
	manager.update();

	for (auto cc : colliders) {
		Collision::AABB(newPlayer.getComponent<Collider2D>(), *cc);
	}
}

void Game::renderPlayer() {
	this->player->render(this->window);
}

void Game::render() {
	this->window.clear();

	// Render
	this->tileMap.render(this->window);
	this->renderPlayer();

	this->window.draw(newPlayer.getComponent<SpriteComponent>().GetSprite());

	this->window.draw(Tile0.getComponent<SpriteComponent>().GetSprite());
	this->window.draw(Tile1.getComponent<SpriteComponent>().GetSprite());
	this->window.draw(Tile2.getComponent<SpriteComponent>().GetSprite());

	// COLLISION DEBUG
	//this->window.draw(newPlayer.getComponent<Collider2D>().collider);
	//this->window.draw(newWall.getComponent<Collider2D>().collider);
	//

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const {
	return this->window;
}