#pragma once

#include "stdafx.h"
#include "Components.h"
#include "Game.h"

class SpriteComponent : public Component {
private:
	Transform* transform;
	sf::Texture *textureSheet; 
	sf::Sprite sprite;
	sf::RectangleShape spriteDebugBounds;

	float xOffset;
	float yOffset;
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
		spriteDebugBounds.setFillColor(sf::Color::Transparent);
		spriteDebugBounds.setOutlineColor(sf::Color::Red);
		spriteDebugBounds.setOutlineThickness(1.f);
		spriteDebugBounds.setPosition(this->sprite.getPosition());
		spriteDebugBounds.setSize(sf::Vector2f(newFrame.width, newFrame.height));
	}

	void SetSpritePosition(float offsetX, float offsetY) {
		this->xOffset = offsetX + sprite.getPosition().x;
		this->yOffset = offsetY + sprite.getPosition().y;
		sprite.setPosition(xOffset, yOffset);
		spriteDebugBounds.setPosition(xOffset, yOffset);
	}

	void SetRotationOfSprite(int angle) {
		sprite.setRotation(angle);
	}

	void init() override {
		transform = &entity->getComponent<Transform>();
	}

	void update() override {
		sprite.setPosition(transform->position.x, transform->position.y);
		//sprite.scale(sf::Vector2f(transform->width, transform->height));
	}

	void draw() override {
		//TextureManager::Draw(&sprite, // WIN);
	}

	sf::RectangleShape GetDebugSpriteIntRect() {
		return spriteDebugBounds;
	}
};