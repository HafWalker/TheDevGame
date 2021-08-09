#include "stdafx.h"
#include "GameState.h"
#include "Map.h"

Manager manager;

std::vector<Collider2D*> GameState::colliders;
std::vector<TileComponent*> GameState::Tiles;
std::vector<PointComponent*> GameState::Points;
std::vector<EnemyComponent*> GameState::Enemies;

auto& newPlayer(manager.addEntity());
auto& newPlayerAttackArea(manager.addEntity());

auto& exitEntity(manager.addEntity());

void GameState::initVariables() {
	std::cout << "Init Variables" << std::endl;
	keyPressed_Space = false;
	isPlayerJumping = false;
	inPlayerAttacking = false;
	this->initFonts();

	this->pauseMenu = new PauseMenu(this->window, this->view);
	this->pauseMenu->init();

	this->endOfLevel = new EndOfLevel(this->window, this->view);
	this->endOfLevel->init();

	this->playerGUI = new PlayerGUI(this->window, this->view);
	this->playerGUI->init();

	//Map::LoadMap("../Assets/Sprites/Maps/Level1_16x12.map", 16,12);
	//Map::LoadMap("../Assets/Sprites/Maps/Level2_32x21.map", 32, 21);
	Map::LoadMap("../Assets/Maps/LEVEL_0.map", 63, 20);
	//Map::LoadMap("../Assets/Sprites/Maps/Level1_TEST.map", 16, 12);

	newPlayer.addComponent<Transform>(100, 250, 100, 55, 1);
	newPlayer.addComponent<SpriteComponent>("../Assets/Animation/Player_Full_SpriteSheet.png");
	newPlayer.addComponent<AnimatorComponent>(128, 128);
	newPlayer.addComponent<Collider2D>("Player",0.f,0.f);
	newPlayer.addComponent<Rigidbody2D>();
	newPlayer.addComponent<PlayerDataComponent>(10);

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
	
	// Exit
	exitEntity.addComponent<Transform>(43 * 50, 19 * 50, 50, 50, 1);
	exitEntity.addComponent<Collider2D>("Exit", 0.f, 0.f);
	exitEntity.addComponent<SpriteComponent>("../Assets/Animation/ExitDoorAnimation.png");
	exitEntity.addComponent<AnimatorComponent>(52,100);
	exitEntity.getComponent<AnimatorComponent>().SetAnimationOffset(0.f,-50.f);
	exitEntity.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ PUERTA_CERRADA,0,1 });
	exitEntity.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ PUERTA_ABRIENDO,0,40 });
	exitEntity.getComponent<AnimatorComponent>().AddAnimationSetting(AnimationSetting{ PUERTA_ABIERTA,0,1 });
	exitEntity.getComponent<AnimatorComponent>().setAnimationState(PUERTA_CERRADA);

	// Init View Center
	this->view->setCenter(sf::Vector2f(newPlayer.getComponent<Transform>().position.x, newPlayer.getComponent<Transform>().position.y));

	std::cout << "TEST INIT: " << this->highscore->currentPlayer << std::endl;
}

void GameState::initFonts() {
	if (!this->font.loadFromFile("../Assets/Fonts/rainyhearts/rainyhearts.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

GameState::GameState(sf::RenderWindow* window, sf::View* view, HighScore* highscore, std::stack<State*>* states) : State(window, view, highscore, states) {
	this->window = window;
	this->view = view;
	this->highscore = highscore;
	initVariables();
}

GameState::~GameState() {
	delete this->pauseMenu;
	delete this->endOfLevel;
	delete this->playerGUI;
}

void GameState::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 50, 50, id);
}

void GameState::PlacePoint(int id, int x, int y) {
	auto& newPoint(manager.addEntity());
	newPoint.addComponent<PointComponent>(x, y, 50, 50, id);
}

void GameState::PlaceEnemy(int id, int x, int y) {
	auto& newEnemy(manager.addEntity());
	newEnemy.addComponent<EnemyComponent>(x, y, 50, 50, id);
}

void GameState::endState() {
	std::cout << "Ending game stuff" << std::endl;
}

void GameState::updateKeybinds(const float& st) {
	this->checkForQuit();
}

void GameState::updatePlayerInput() {
	this->window->pollEvent(ev);
	if (!isGamePaused) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !inPlayerAttacking) {
			newPlayer.getComponent<Rigidbody2D>().move(Vector2D(-0.075f, 0.f));
			if (!isPlayerJumping) {
				newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::MOVING_LEFT);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !inPlayerAttacking) {
			newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.075f, 0.f));
			if (!isPlayerJumping) {
				newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::MOVING_RIGHT);
			}
		}

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, -0.075f));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, 0.075f));
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !keyPressed_Space) {
			keyPressed_Space = true;
			isPlayerJumping = true;
			newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::FALLING);
			//std::cout << "JUMP" << std::endl;
			newPlayer.getComponent<Rigidbody2D>().Jump(Vector2D(0.f, -40.f));
			//newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, -2.f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && !inPlayerAttacking) {
			inPlayerAttacking = true;
			newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::ATTACK);
			//newPlayer.getComponent<Rigidbody2D>().move(Vector2D(0.f, -2.f));
		}

		if (ev.type == sf::Event::KeyReleased) {
			if (ev.key.code == sf::Keyboard::Space && keyPressed_Space) {
				keyPressed_Space = false;
				//std::cout << "JUMP RELEASE" << std::endl;
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
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && !isPausePressed) {
		std::cout << "Game Pause" << std::endl;
		isPausePressed = true;
		isGamePaused = !isGamePaused;
	}

	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::P && isPausePressed) {
			std::cout << "Game Continue" << std::endl;
			isPausePressed = false;
		}
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
			}

			if (collisionInfo.tag == "Collider") {
				newPlayer.getComponent<Rigidbody2D>().move(collisionInfo.displacement * 0.02f);
				newPlayer.getComponent<Transform>().position = newPlayer.getComponent<Transform>().position + collisionInfo.displacement;
				if (collisionInfo.displacement.y > 0) {
					newPlayer.getComponent<Rigidbody2D>().Jump(Vector2D(0.f, 0.f));
					//std::cout << "Colliding with ceiling" << std::endl;
				}
			}

			if (collisionInfo.tag == "Collider" && isPlayerJumping && newPlayer.getComponent<AnimatorComponent>().getAnimationEnd(ANIMATION_STATES::FALLING)) {
				isPlayerJumping = false;
				newPlayer.getComponent<AnimatorComponent>().setAnimationState(ANIMATION_STATES::IDLE);
			}

			if (collisionInfo.tag == "Point" && cc->isActive) {
				cc->SetColliderActive(false);
				cc->entity->getComponent<PointComponent>().SwitchPointAnimation();
				this->highscore->ChangeScore(this->highscore->currentPlayer, 100);
				std::cout << "AddPoint to" << this->highscore->currentPlayer << "score" << std::endl;
			}

			if (collisionInfo.tag == "Enemy" && cc->isActive) {
				//cc->SetColliderActive(false);
				newPlayer.getComponent<AnimatorComponent>().setAnimationState(TAKE_DAMAGE);
				newPlayer.getComponent<Rigidbody2D>().move(collisionInfo.displacement * 0.5f);
				newPlayer.getComponent<Transform>().position = newPlayer.getComponent<Transform>().position + collisionInfo.displacement;
				newPlayer.getComponent<PlayerDataComponent>().SetHealt(newPlayer.getComponent<PlayerDataComponent>().GetHealt() - 1);
				std::cout << "Player Hit by enemy" << std::endl;
			}

			if (collisionInfo.tag == "Exit" && cc->isActive && !isEndOfLevel) {
				//this->isLoadingLevel = true;
				isGamePaused = true;
				isEndOfLevel = true;

				this->endOfLevel->SetPlayerScoreToShow(std::to_string(this->scoreValue));

				std::cout << "End of LEVEL" << std::endl;
			}
		}
	}
}

void GameState::update(const float& dt) {
	this->updatePlayerInput();

	if (!isGamePaused) {
		manager.update();
	}
	this->updateKeybinds(dt);
	this->updateCollision();
	this->updateView(dt);

	this->playerGUI->update();
	this->playerGUI->SetHealt(newPlayer.getComponent<PlayerDataComponent>().GetHealt());

	if (newPlayer.getComponent<Transform>().velocity.y > 0.f) {
		keyPressed_Space = false;
	}

	newPlayer.getComponent<AnimatorComponent>().updateDeltaTime(dt);
	newPlayer.getComponent<Rigidbody2D>().update(dt);

	exitEntity.getComponent<AnimatorComponent>().updateDeltaTime(dt);
	// NEED TO UPDATE DT
	//newPoint.getComponent<AnimatorComponent>().updateDeltaTime(dt);

	newPlayerAttackArea.getComponent<Transform>().position = newPlayer.getComponent<Transform>().position;
	updateEnemys(dt);
	updateMapAnimations(dt);
	//Map::LoadMap("D:/THE_DEV_GAME/PROYECT/Sprites/Maps/Level1_16x12.map", 16, 12);

	// DOOR LOGIC

	sf::Vector2f PlayerToDoorDistance = sf::Vector2f(
		exitEntity.getComponent<Transform>().position.x - newPlayer.getComponent<Transform>().position.x,
		exitEntity.getComponent<Transform>().position.y - newPlayer.getComponent<Transform>().position.y
	);

	//std::cout << PlayerToDoorDistance << std::endl;
	//std::cout << isPlayerCloseToDoor << std::endl;

	if (PlayerToDoorDistance.x < 250 && PlayerToDoorDistance.y < 250 && !isPlayerCloseToDoor) {
		isPlayerCloseToDoor = true;
		exitEntity.getComponent<AnimatorComponent>().setAnimationState(PUERTA_ABRIENDO);
	}
	else if(PlayerToDoorDistance.x >= 200 && PlayerToDoorDistance.y >= 200 && isPlayerCloseToDoor) {
		exitEntity.getComponent<AnimatorComponent>().setAnimationState(PUERTA_CERRADA);
		isPlayerCloseToDoor = false;
	}

	// END GAME AND MENUES

	if (newPlayer.getComponent<PlayerDataComponent>().GetHealt() < 0) {
		isGamePaused = true;
		isEndOfLevel = true;
	}

	if (isGamePaused) {
		this->updateMousePositions();
		if (!isEndOfLevel) {
			this->pauseMenu->update();
			this->pauseMenu->updatePauseMenuButtons(this->mousePositionView);
			if (this->pauseMenu->btn_Continue->isPressed()) {
				isPausePressed = true;
				isGamePaused = false;
				isPausePressed = false;
			}
			if (this->pauseMenu->btn_exit->isPressed()) {
				isPausePressed = true;
				isGamePaused = false;
				this->QuitState();
			}
		}
		else {
			this->endOfLevel->update();
			this->endOfLevel->updatePauseMenuButtons(this->mousePositionView);
			if (this->endOfLevel->btn_Continue->isPressed()) {
				isPausePressed = true;
				isGamePaused = false;
				isPausePressed = false;
			}
			if (this->endOfLevel->btn_exit->isPressed()) {
				isPausePressed = true;
				isGamePaused = false;
				this->QuitState();
			}
		}
	}
}

void GameState::updateEnemys(const float& dt) {
	
}

void GameState::updateMapAnimations(const float& dt) {
	for (auto cc : Points) {
		cc->entity->getComponent<AnimatorComponent>().updateDeltaTime(dt);
	}

	for (auto cc : Enemies) {
		cc->entity->getComponent<AnimatorComponent>().updateDeltaTime(dt);
	}
}

void GameState::updateView(const float& dt) {
	sf::Vector2f playersPosition = sf::Vector2f(newPlayer.getComponent<Transform>().position.x, newPlayer.getComponent<Transform>().position.y);
	sf::Vector2f movement = playersPosition - this->view->getCenter();
	this->view->move(sf::Vector2f(movement * dt * 2.f));

	// Set the Score text in the top left of the view
	this->scoreValue = this->highscore->GetScore(this->highscore->currentPlayer).first;
	this->playerGUI->SetScore(this->scoreValue);
}

void GameState::render(sf::RenderTarget* target) {

	this->window->setView(*view);

	// Renders DEBUGS
	for (auto cc : Tiles) {
		this->window->draw(cc->entity->getComponent<SpriteComponent>().GetSprite());
		if (cc->entity->hasComponents<Collider2D>()) {
			//this->window->draw(cc->entity->getComponent<Collider2D>().collider);
		}
	}

	for (auto cc : Points) {
		this->window->draw(cc->entity->getComponent<SpriteComponent>().GetSprite());
		if (cc->entity->hasComponents<Collider2D>()) {
			//this->window->draw(cc->entity->getComponent<Collider2D>().collider);
		}
	}

	for (auto cc : Enemies) {
		this->window->draw(cc->entity->getComponent<SpriteComponent>().GetSprite());
		if (cc->entity->hasComponents<Collider2D>()) {
			//this->window->draw(cc->entity->getComponent<Collider2D>().collider);
		}
	}

	this->window->draw(newPlayer.getComponent<SpriteComponent>().GetSprite());
	this->window->draw(exitEntity.getComponent<SpriteComponent>().GetSprite());

	//TextureManager::Draw(newPlayer.getComponent<SpriteComponent>().GetSprite());

	// COLLISION DEBUG
	//this->window->draw(newPlayerAttackArea.getComponent<Collider2D>().collider);
	//this->window->draw(newPlayer.getComponent<Collider2D>().collider);
	//this->window->draw(newPoint.getComponent<Collider2D>().collider);
	//this->window->draw(exitEntity.getComponent<Collider2D>().collider);
	//

	// SPRITES DEBUG
	//this->window->draw(newEnemy.getComponent<SpriteComponent>().GetDebugSpriteIntRect());
	//

	// UI - RENDER

	this->playerGUI->render(this->window);

	if (isGamePaused) {
		if (!isEndOfLevel) {
			this->pauseMenu->render(this->window);
		}
		else {
			this->endOfLevel->render(this->window);
		}
	}
}

void GameState::ClearMap() {
	for (auto cc : Tiles) {
		delete cc;
	}
}
