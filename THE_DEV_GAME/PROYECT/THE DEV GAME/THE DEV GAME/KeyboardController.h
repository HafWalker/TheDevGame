#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	Transform* transform;

	void init() override {
		transform = &entity->getComponent<Transform>();
	}

	/*void update() override {
		if(Game::ev.type == sf::Event::KeyPressed) {
			switch (Game::ev.key.code) {
			case sf::Keyboard::A:
				transform->velocity.x = -5.f;
				break;
			case sf::Keyboard::D:
				transform->velocity.x = 5.f;
				break;
			case sf::Keyboard::W:
				transform->velocity.y = -5.f;
				break;
			case sf::Keyboard::S:
				transform->velocity.y = 5.f;
				break;
			default:
				break;
			}
		}
	}*/
};