#pragma once
#include <string>
#include "stdafx.h"

class Collider2D : public Component {
public:
	sf::RectangleShape collider;
	std::string tag;

	Transform* transform;

	Collider2D(std::string t) {
		tag = t;
	}

	void init() override {
		if (!entity->hasComponents<Transform>()) {
			entity->addComponent<Transform>();
		}
		transform = &entity->getComponent<Transform>();
		Game::colliders.push_back(this);

		// For Debug
		collider.setFillColor(sf::Color::Transparent);
		collider.setOutlineColor(sf::Color::Green);
		collider.setOutlineThickness(1.f);
	}

	void update() override {
		collider.setPosition(transform->position.x, transform->position.y);
		/// En caso de modificar la escala de los elementos InGame es necesario multiplicar el Size * Transform.Scale
		collider.setSize(sf::Vector2f(transform->width, transform->height));
	}
};