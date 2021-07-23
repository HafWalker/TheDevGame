#pragma once
#include "ECS.h"
#include "Vector2D.h"

struct Transform : public Component {
public:
	Vector2D position;
	Vector2D velocity;
	float velocityMax;
	float aceleration;
	float velocityMin;
	float dragCoefficient;
	float speed = 1;

	int height = 32;
	int width = 32;
	int scale = 1;

	Transform() {
		position.x = 0.f;
		position.y = 0.f;
	}

	Transform(float x, float y) {
		position.x = x;
		position.y = y;
	}

	Transform(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocityMax = 10.f;
		aceleration = 3.f;
		velocityMin = 0.01f;
		dragCoefficient = 0.8f;
		speed = 8.f;
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		if (velocity.x > 1.f) { velocity.x = 1.f; }
		if (velocity.x < -1.f) { velocity.x = -1.f; }
		if (velocity.y > 1.f) { velocity.y = 1.f; }
		if (velocity.y < -1.f) { velocity.y = -1.f; }

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		//ActiveDrag();

		//std::cout << velocity.x << std::endl;
	}

	void Translate(Vector2D direction) {
		// Aceleration
		velocity.x += direction.x * aceleration;

		// Limit Velocity
		if (std::abs(this->velocity.x) > velocityMax) {
			velocity.x = velocityMax * ((velocity.x < 0.f) ? -1.f : 1.f);
		}
	}


	void ActiveDrag() {
		// Deceleration
		velocity.x *= dragCoefficient;
		velocity.y *= dragCoefficient;

		//Limit deceleration
		if (std::abs(velocity.x) < velocityMin) {
			velocity.x = 0;
		}
		if (std::abs(velocity.y) < velocityMin) {
			velocity.y = 0;
		}
	}
};