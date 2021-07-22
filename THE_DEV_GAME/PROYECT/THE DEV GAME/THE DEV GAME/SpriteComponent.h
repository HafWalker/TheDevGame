#pragma once

#include "stdafx.h"
#include "Components.h"

class SpriteComponent : public Component {
private:
	Transform* position;
	sf::Texture *textureSheet; 
	sf::Sprite sprite;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		textureSheet = TextureManager::LoadTexture("D:/THE_DEV_GAME/PROYECT/Sprites/Animation/spritesheet_Full.png");
	}

	void init() override {
		position = &entity->getComponent<Transform>();
		sprite.setPosition(0.f, 0.f);
	}

	void update() override {
		sprite.move(position->x(), position->y());
	}

	void draw() override {
		// TODO: Draw with the windows reference
		// https://www.youtube.com/watch?v=jq3Bg7XXjWw&t=10s
	}
};