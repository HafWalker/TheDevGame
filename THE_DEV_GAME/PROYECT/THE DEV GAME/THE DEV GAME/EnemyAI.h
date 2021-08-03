#pragma once

#include "stdafx.h"
#include "Game.h"

class EnemyAI : public Component {
private:
	float m_direction;
	float m_speed;
	float m_maxDistance;
	Vector2D m_vectorDirection;

	float m_displacementMaxValue;
	float m_displacementMinValue;

	float attackTime;
	float timerCounter;

public:
	Rigidbody2D* rigidbody2D;
	Transform* transform;

	bool isAlive;

	EnemyAI(Vector2D direction, float speed, float maxValue) {
		m_vectorDirection = direction;
		m_speed = speed;
		m_maxDistance = maxValue;
	}

	void init() override {
		if (!entity->hasComponents<Transform>()) {
			entity->addComponent<Transform>();
		}
		transform = &entity->getComponent<Transform>();

		if (!entity->hasComponents<Rigidbody2D>()) {
			entity->addComponent<Rigidbody2D>();
		}

		m_displacementMaxValue = transform->position.x + (m_maxDistance * m_vectorDirection.x);
		m_displacementMinValue = transform->position.x;

		rigidbody2D = &entity->getComponent<Rigidbody2D>();
		m_direction = 1.f;
		timerCounter = 0.f;
		attackTime = 0.f;
		isAlive = true;
	}

	void update() override {
		if (this->isAlive) {
			CheckMovement();
			rigidbody2D->move(Vector2D(m_vectorDirection.x * m_direction * m_speed, m_vectorDirection.y * m_direction * m_speed));
			rigidbody2D->Drag();
		}
	}

	void CheckMovement() {
		if (transform->position.x > m_displacementMaxValue) {
			m_direction = -1.f;
		}
		else if (transform->position.x < m_displacementMinValue) {
			m_direction = 1.f;
		}
	}

	bool GetAttackTrigger() {
		if (timerCounter > attackTime) {
			timerCounter = 0.f;
			return true;
		} else {
			return false;
		}
	}

	void UpdateDeltaTime(const float& dt) {
		this->timerCounter += dt;
	}

	void SetAttackTimer(float time) {
		this->attackTime = time;
	}

	void TakeDamage() {
		this->isAlive = false;
	}
};