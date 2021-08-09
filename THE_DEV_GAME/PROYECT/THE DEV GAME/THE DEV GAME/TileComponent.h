#pragma once

#include "stdafx.h"

class TileComponent : public Component {
public:
	Transform* trasnform;
	SpriteComponent* sprite;

	int angleOfRotation = 0;
	sf::Vector2f positionForRotation = sf::Vector2f(0.f,0.f);

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
			path = "../Assets/SciFi_Wall_00.png"; // Asset 1 (Tile_Horizontal)
			break;
		case 1:

			break;
		case 2:
			path = "../Assets/SciFi_Platform_00.png"; // Asset 3
			break;
		case 3:
			path = "../Assets/SciFi_Column_00.png"; // Asset 3 (Tile Tile_Vertical)
			break;
		case 4:

			break;
		case 5:

			break;
		case 6:
			// ENTITY ENEMY SPAWN, NEED BACKGROUND TILE
			path = "../Assets/SciFi_Wall_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 7:
			// ENTITY POINT SPAWN, NEED BACKGROUND TILE
			path = "../Assets/SciFi_Wall_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 8:
			path = "../Assets/SciFi_Floor_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 9:
			angleOfRotation = 180;
			positionForRotation = sf::Vector2f(50.f, 50.f);
			path = "../Assets/SciFi_Floor_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 10:
			// CORNER BOTTOM LEFT
			path = "../Assets/SciFi_Corner_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 11:
			// CORNER TOP LEFT
			angleOfRotation = 90;
			positionForRotation = sf::Vector2f(0.f,50.f);
			path = "../Assets/SciFi_Corner_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 12:
			// CORNER TOP RIGHT
			angleOfRotation = 180;
			positionForRotation = sf::Vector2f(50.f, 50.f);
			path = "../Assets/SciFi_Corner_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 13:
			// CORNER BOTTOM RIGHT
			angleOfRotation = 270;
			positionForRotation = sf::Vector2f(50.f, 0.f);
			path = "../Assets/SciFi_Corner_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 14:
			angleOfRotation = 90;
			positionForRotation = sf::Vector2f(0.f, 50.f);
			path = "../Assets/SciFi_Floor_00.png"; // Asset 4 (Tile Tile_TADerecha)
			break;
		case 15:
			angleOfRotation = 270;
			positionForRotation = sf::Vector2f(50.f, 0.f);
			path = "../Assets/SciFi_Floor_00.png"; // Asset 4 (Tile Tile_TADerecha)
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
		sprite->SetRotationOfSprite(angleOfRotation);
		sprite->SetOrigin(positionForRotation.x, positionForRotation.y);
		if (tileID == 2 || 
			tileID == 3 || 
			tileID == 8 ||
			tileID == 9 ||
			tileID == 10 ||
			tileID == 11 ||
			tileID == 12 ||
			tileID == 13 ||
			tileID == 14 ||
			tileID == 15
			) {
			entity->addComponent<Collider2D>("Collider", 0.f, 0.f);
		}
		GameState::Tiles.push_back(this);
	}
};