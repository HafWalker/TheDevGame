#pragma once
#include "stdafx.h"
#include <string>

class Collider2D;

struct CollisionInfo {
	std::string tag;
	bool isColliding = false;
	Vector2D diff = Vector2D().Zero();
	Vector2D displacement = Vector2D().Zero();
};

class Collision {
public:
	static CollisionInfo AABB(const sf::RectangleShape& recA, const sf::RectangleShape& recb);
	static CollisionInfo AABB(const Collider2D& colA, const Collider2D& colB);
};