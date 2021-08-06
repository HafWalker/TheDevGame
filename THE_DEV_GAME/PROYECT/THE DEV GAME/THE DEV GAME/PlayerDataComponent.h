#pragma once

#include "stdafx.h"
#include "Game.h"

class PlayerDataComponent : public Component {
public:
	float playerHealth;

	PlayerDataComponent(int health) {
		this->playerHealth = health;
	}

	void init() override {
	
	}

	void update() override {
	
	}

	int GetHealt() {
		return this->playerHealth;
	}

	void SetHealt(int value) {
		if (this->playerHealth > 0) {
			this->playerHealth = value;
		}
	}
};