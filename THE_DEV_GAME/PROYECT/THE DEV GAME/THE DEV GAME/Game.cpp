#include "stdafx.h"
#include "Game.h"

void Game::initVariables() {
	
}

void Game::initWindow() {
	this->window.create(sf::VideoMode(800, 600), "The Dev Game", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initTileMap() {
	//this->tileMap = new TileMap();
}

void Game::initPlayer() {
	this->player = new Player();
}

Game::Game() {
	this->initWindow();
	this->initTileMap();
	this->initPlayer();
}

Game::~Game() {
	delete this->player;
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
	while (this->window.pollEvent(this->ev)) {
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
	}

	this->updatePlayer();
	this->updateCollision();
}

void Game::renderPlayer() {
	this->player->render(this->window);
}

void Game::render() {
	this->window.clear();

	// Render
	this->tileMap.render(this->window);
	this->renderPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const {
	return this->window;
}

void Game::log(std::string str) {
	std::cout << "Log: " << str << "\n";
}


