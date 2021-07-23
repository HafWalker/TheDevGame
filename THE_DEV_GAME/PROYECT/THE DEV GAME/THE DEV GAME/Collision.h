#pragma once
#include "stdafx.h"

class Collider2D;

class Collision {
public:
	static bool AABB(const sf::RectangleShape& recA, const sf::RectangleShape& recb);
	static bool AABB(const Collider2D& colA, const Collider2D& colB);
};