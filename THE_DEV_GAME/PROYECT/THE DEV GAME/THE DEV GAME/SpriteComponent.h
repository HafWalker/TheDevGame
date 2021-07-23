#pragma once

#include "stdafx.h"
#include "Components.h"

class SpriteComponent : public Component {
private:
	Transform* transform;
	sf::Texture textureSheet; 
	sf::Sprite sprite;
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		if (!textureSheet.loadFromFile(path)) {
			std::cout << "ERROR LOADING TEXTURESHEET" << "\n";
		}
		sprite.setTexture(textureSheet);
	}

	sf::Texture GetTexture() {
		return textureSheet;
	}

	sf::Sprite GetSprite() {
		return sprite;
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
		//TextureManager::RenderTexture(renderTarget, sprite);
	}
};