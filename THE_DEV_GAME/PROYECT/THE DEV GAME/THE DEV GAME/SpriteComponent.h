#pragma once

#include "stdafx.h"
#include "Components.h"
#include "Game.h"

class SpriteComponent : public Component {
private:
	Transform* transform;
	sf::Texture *textureSheet; 
	sf::Sprite sprite;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		textureSheet = TextureManager::LoadTexture(path);
		sprite.setTexture(*textureSheet);
	}

	sf::Texture GetTexture() {
		return *textureSheet;
	}

	sf::Sprite GetSprite() {
		return sprite;
	}

	void SetOrigin(float xPos, float yPos) {
		sprite.setOrigin(sf::Vector2f(xPos, yPos));
	}

	void SetScale(float xScale, float yScale) {
		sprite.setScale(sf::Vector2f(xScale, yScale));
	}

	void SetFrame(sf::IntRect newFrame) {
		this->sprite.setTextureRect(newFrame);
	}

	void init() override {
		transform = &entity->getComponent<Transform>();
		sprite.setPosition(0.f, 0.f);
	}

	void update() override {
		sprite.setPosition(transform->position.x, transform->position.y);
		//sprite.scale(sf::Vector2f(transform->width, transform->height));
	}

	void draw() override {
		//TextureManager::Draw(&sprite, // WIN);
	}
};