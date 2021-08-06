#pragma once

#include "stdafx.h"

class PointComponent : public Component {
public:
	sf::Vector2f position;

	Transform* trasnform;
	SpriteComponent* sprite;
	AnimatorComponent* animator;
	Collider2D* collider2D;

	PointComponent() = default;
	PointComponent(int x, int y, int w, int h, int id) {
		position.x = x;
		position.y = y;
	}

	void init() override {
		entity->addComponent<Transform>(position.x,	position.y,	50,	50,	1);
		trasnform = &entity->getComponent<Transform>();
		entity->addComponent<SpriteComponent>("../Assets/Animation/spritesheet_point.png");
		sprite = &entity->getComponent<SpriteComponent>();
		entity->addComponent<AnimatorComponent>(128, 128);
		animator = &entity->getComponent<AnimatorComponent>();
		entity->addComponent<Collider2D>("Point", 0.f, 0.f);
		collider2D = &entity->getComponent<Collider2D>();

		animator->AddAnimationSetting(AnimationSetting{ IDLE,0,81 });
		animator->setAnimationState(IDLE);
		animator->SetAnimationOffset(-39.f, -40.f);

		GameState::Points.push_back(this);
	}

	void update() override {

	}
};