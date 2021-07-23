#include "stdafx.h"
#include "Collision.h"

bool Collision::AABB(const sf::RectangleShape& recA, const sf::RectangleShape& recB) {
	if (
		recA.getPosition().x + recA.getSize().x >= recB.getPosition().x &&
		recB.getPosition().x + recB.getSize().x >= recA.getPosition().x &&
		recA.getPosition().y + recA.getSize().y >= recB.getPosition().y &&
		recB.getPosition().y + recB.getSize().y >= recA.getPosition().y
		) {
		return true;
	} else {
		return false;
	}
}

bool Collision::AABB(const Collider2D& colA, const Collider2D& colB) {
	if (AABB(colA.collider, colB.collider)) {
		std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	} else {
		return false;
	}
}
