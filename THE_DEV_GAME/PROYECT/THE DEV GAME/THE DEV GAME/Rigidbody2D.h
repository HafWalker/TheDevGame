#pragma once

#include "stdafx.h"
#include "Game.h"

class Rigidbody2D : public Component {
public:
	float gravity = 0.3f;
	Transform* transform;

	float gravityMaxSpeed;
	float velocityMax;
	float aceleration;
	float velocityMin;
	float dragCoefficient;

	Rigidbody2D() {
	}

	void init() override {
		if (!entity->hasComponents<Transform>()) {
			entity->addComponent<Transform>();
		}
		transform = &entity->getComponent<Transform>();

		gravityMaxSpeed = 2.5f;
		velocityMax = 15.f;
		aceleration = 3.f;
		velocityMin = 0.01f;
		dragCoefficient = 0.8f;
	}

	void update() override {
		transform->velocity.Add(Vector2D(0.f, gravity));
		if (transform->velocity.y > gravityMaxSpeed) { transform->velocity.y = gravityMaxSpeed; }
		Drag();
	}

	void move(Vector2D vectorDirection) {
		// Aceleration
		transform->velocity.x += vectorDirection.x * aceleration;

		// Limit Velocity
		if (std::abs(transform->velocity.x) > velocityMax) {
			transform->velocity.x = velocityMax * ((transform->velocity.x < 0.f) ? -1.f : 1.f);
		}

		// Aceleration
		transform->velocity.y += vectorDirection.y * aceleration;

		// Limit Velocity
		if (std::abs(transform->velocity.y) > velocityMax) {
			transform->velocity.y = velocityMax * ((transform->velocity.y < 0.f) ? -1.f : 1.f);
		}
	}

	void Drag() {
		// Deceleration
		transform->velocity.x *= dragCoefficient;
		transform->velocity.y *= dragCoefficient;

		//Limit deceleration
		if (std::abs(transform->velocity.x) < velocityMin) {
			transform->velocity.x = 0;
		}
		if (std::abs(transform->velocity.y) < velocityMin) {
			transform->velocity.y = 0;
		}
	}
};