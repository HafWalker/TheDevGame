#pragma once

#include "stdafx.h"

class EnemyComponent : public Component {
public:
	sf::Vector2f position;

	Transform* trasnform;
	SpriteComponent* sprite;
	AnimatorComponent* animator;
	Collider2D* collider2D;
	Rigidbody2D* rigidbody2D;
	EnemyAI* enemyAI;

	EnemyComponent() = default;
	EnemyComponent(int x, int y, int w, int h, int id) {
		position.x = x;
		position.y = y;
	}

	void init() override {
		entity->addComponent<Transform>(position.x, position.y, 50, 50, 1);
		trasnform = &entity->getComponent<Transform>();
		entity->addComponent<SpriteComponent>("../Assets/Animation/enemy_onlyAttack.png");
		sprite = &entity->getComponent<SpriteComponent>();
		entity->addComponent<AnimatorComponent>(100, 100);
		animator = &entity->getComponent<AnimatorComponent>();
		entity->addComponent<Collider2D>("Enemy", 0.f, -25.f);
		collider2D = &entity->getComponent<Collider2D>();
		entity->addComponent<Rigidbody2D>();
		rigidbody2D = &entity->getComponent<Rigidbody2D>();
		entity->addComponent<EnemyAI>(Vector2D(1.f, 0.f), 0.05f, 500.f);
		enemyAI = &entity->getComponent<EnemyAI>();

		rigidbody2D->gravity = 0.f;
		animator->AddAnimationSetting(AnimationSetting{ IDLE,0,81 });
		animator->setAnimationState(IDLE);
		animator->SetAnimationOffset(-25.f, -50.f);

		GameState::Enemies.push_back(this);
	}

	void update() override {

	}
};