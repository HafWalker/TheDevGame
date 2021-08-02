#include "stdafx.h"
#include "Game.h"
#include "Map.h"

void Game::initVariables() {
	std::cout << "Init GAME Variables" << std::endl;
	// Scores init
	this->highscoreManager = new HighScore();
	this->highscoreManager->AddScore("NewPlayer", 0);
}

void Game::initView() {
	this->view = new sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(1024.f, 920.f));
}

void Game::initWindow() {
	std::cout << "Init Window: GAME" << std::endl;
	this->window = new sf::RenderWindow(sf::VideoMode(1024, 920), "The Dev Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initStates() {
	this->states.push(new MainMenuState(this->window, this->view, &this->states));
}

Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initView();
	this->initStates();
}

Game::~Game() {
	delete this->window;
	delete this->view;
	delete this->highscoreManager;
	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateDeltaTime() {
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::handleEvents() {
	/// <summary>
	/// MOVER AL GAME STATE
	/// </summary>
	this->window->pollEvent(ev);
	switch (ev.type) {
	case sf::Event::Closed:
		// Commented to prevent a weird bug (Open and instan close the game)
		//this->window.close();
		break;
	case sf::Event::KeyPressed:
		if (ev.key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
		break;
	default:
		break;
	}
}

void Game::update() {
	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else {
		// End the application
	}

	this->handleEvents();
}

void Game::render() {
	this->window->clear();

	if (!this->states.empty()) {
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void Game::run() {
	while (this->window->isOpen()) {
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}