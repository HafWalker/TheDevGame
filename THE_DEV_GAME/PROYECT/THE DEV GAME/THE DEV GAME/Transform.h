#pragma once
#include "ECS.h"
#include "Vector2D.h"

struct Transform : public Component {
public:
	Vector2D position;
	Vector2D velocity;
	Vector2D vectorCollision;
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
		speed = 8.f;
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {		
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

		//ActiveDrag();

		//std::cout << velocity.x << std::endl;
	}

	void TranslateNormalized(Vector2D vectorDirection) {
		if (vectorDirection.x > 1.f) { velocity.x = 1.f; }
		if (vectorDirection.x < -1.f) { velocity.x = -1.f; }
		if (vectorDirection.y > 1.f) { velocity.y = 1.f; }
		if (vectorDirection.y < -1.f) { velocity.y = -1.f; }
	}

	void Translate(Vector2D vectorDirection) {
		velocity.Add(vectorDirection);
	}

	void DetectCollision(Vector2D vectorOfCollision) {
		if (vectorOfCollision.x > 1.f) { velocity.x = 0.f; }
		if (vectorOfCollision.x < -1.f) { velocity.x = 0.f; }
		if (vectorOfCollision.y > 1.f) { velocity.y = 0.f; }
		if (vectorOfCollision.y < -1.f) { velocity.y = 0.f; }
		//position += vectorOfCollision;
		vectorCollision = vectorOfCollision;
	}
};