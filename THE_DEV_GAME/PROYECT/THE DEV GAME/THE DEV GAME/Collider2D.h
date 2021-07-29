#pragma once
#include <string>
#include "stdafx.h"

class Collider2D : public Component {
private:
	float m_colliderOffsetX;
	float m_colliderOffsetY;
	float m_width;
	float m_height;
public:
	sf::RectangleShape collider;
	std::string tag;

	Transform* transform;

	Collider2D(std::string t, float offset_X, float offset_Y, float w = 0.f, float h = 0.f) {
		tag = t;
		this->m_colliderOffsetX = offset_X;
		this->m_colliderOffsetY = offset_Y;
		this->m_width = w;
		this->m_height = h;
	}

	void init() override {
		if (!entity->hasComponents<Transform>()) {
			entity->addComponent<Transform>();
		}
		transform = &entity->getComponent<Transform>();
		GameState::colliders.push_back(this);

		// For Debug
		collider.setFillColor(sf::Color::Transparent);
		collider.setOutlineColor(sf::Color::Green);
		collider.setOutlineThickness(1.f);

		/// En caso de modificar la escala de los elementos InGame es necesario multiplicar el Size * Transform.Scale
		if (m_width == 0.f && m_height == 0.f) {
			collider.setSize(sf::Vector2f(transform->width, transform->height));
		} else {
			collider.setSize(sf::Vector2f(m_width, m_height));
		}
	}

	void update() override {
		collider.setPosition(transform->position.x + m_colliderOffsetX, transform->position.y + m_colliderOffsetY);
	}
};