#pragma once

#include "stdafx.h"

class TileComponent : public Component {
public:
	Transform* trasnform;
	SpriteComponent* sprite;

	sf::RectangleShape tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id) {
		tileRect.setPosition(x ,y);
		tileRect.setSize(sf::Vector2f(w, h));
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "D:/THE_DEV_GAME/PROYECT/Sprites/Tile0.png"; // Asset 1
			break;
		case 1:
			path = "D:/THE_DEV_GAME/PROYECT/Sprites/Tile1.png"; // Asset 2
			break;
		case 2:
			path = "D:/THE_DEV_GAME/PROYECT/Sprites/Tile2.png"; // Asset 3
			break;
		default:
			break;
		}
	}

	void init() override {
		entity->addComponent<Transform>(
			tileRect.getPosition().x,
			tileRect.getPosition().y,
			tileRect.getSize().x,
			tileRect.getSize().y,
			1 );
		trasnform = &entity->getComponent<Transform>();
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
		if (tileID == 0) {
			entity->addComponent<Collider2D>("Wall");
		}
		Game::Tiles.push_back(this);
	}
};