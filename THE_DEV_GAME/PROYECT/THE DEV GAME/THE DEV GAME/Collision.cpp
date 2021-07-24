#include "stdafx.h"
#include "Collision.h"

CollisionInfo Collision::AABB(const sf::RectangleShape& recA, const sf::RectangleShape& recB) {
	CollisionInfo colInfo;
	if (
		recA.getPosition().x + recA.getSize().x >= recB.getPosition().x &&
		recB.getPosition().x + recB.getSize().x >= recA.getPosition().x &&
		recA.getPosition().y + recA.getSize().y >= recB.getPosition().y &&
		recB.getPosition().y + recB.getSize().y >= recA.getPosition().y
		) {
		colInfo.isColliding = true;
	} else {
		colInfo.isColliding = false;
		return colInfo;
	}

	Vector2D diff = Vector2D().Zero();
	Vector2D displacement = Vector2D().Zero();

	// Calculo la profundidad
	if (recA.getPosition().x < recB.getPosition().x) { // Vengo por izquierda
		diff.x = recB.getPosition().x - (recA.getPosition().x + recA.getSize().x);
		//std::cout << diff.x << "=" << recB.getPosition().x << "-" << (recA.getPosition().x + recA.getSize().x) << std::endl;
	}
	else if (recA.getPosition().x > recB.getPosition().x) { // Vengo por derecha
		diff.x = recA.getPosition().x - (recB.getPosition().x + recB.getSize().x);
	}
	if (recA.getPosition().y < recB.getPosition().y) { // Vengo por arriba
		diff.y = recB.getPosition().y - (recA.getPosition().y + recA.getSize().y);
	}
	else if (recA.getPosition().y > recB.getPosition().y) { // Vengo por abajo
		diff.y = recA.getPosition().y - (recB.getPosition().y + recB.getSize().y);
	}

	// Calculo el displacement
	if (abs(diff.x) < abs(diff.y)) { // Colision en X
		if (recA.getPosition().x < recB.getPosition().x) { // vengo por izquierda
			displacement.x = diff.x;
		}
		else if (recA.getPosition().x > recB.getPosition().x) { // vengo por derecha
			displacement.x = -diff.x;
		}
	}
	else if (abs(diff.x) > abs(diff.y)) { // Colision en Y
		if (recA.getPosition().y < recB.getPosition().y) { // vengo por arriba
			displacement.y = diff.y;
		}
		else if (recA.getPosition().y > recB.getPosition().y) { // vengo por abajo
			displacement.y = -diff.y;
		}
	}

	//displacement.x = (recA.getPosition().x + recA.getSize().x) - recB.getPosition().x;
	//displacement.y = (recA.getPosition().y + recA.getSize().y) - recB.getPosition().y;

	colInfo.diff = diff;
	colInfo.displacement = displacement;
	return colInfo;
}

CollisionInfo Collision::AABB(const Collider2D& colA, const Collider2D& colB) {
	CollisionInfo colInfo = AABB(colA.collider, colB.collider);
	if (colInfo.isColliding) {
		colInfo.tag = colB.tag;
		return colInfo;
	} else {
		return colInfo;
	}
}
