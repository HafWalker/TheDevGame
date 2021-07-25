#pragma once

#include "stdafx.h"
#include "Components.h"
#include "Game.h"

enum ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING, ATTACK, TAKE_DAMAGE, DIE };

class AnimatorComponent : public Component {
private:
	short animState;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	bool animationSwitch;
public:
	SpriteComponent* spriteComponent;

	AnimatorComponent() = default;

	void init() override {
		if (!entity->hasComponents<SpriteComponent>()) {
			entity->addComponent<SpriteComponent>();
		}
		spriteComponent = &entity->getComponent<SpriteComponent>();
		this->animationTimer.restart();
		this->animationSwitch = true;
		this->animState = ANIMATION_STATES::IDLE;

		//TODO: Define the sheet tile
		this->currentFrame = sf::IntRect(0, 0, 50, 100);
	}

	void update() override {
		if (spriteComponent != nullptr) {
			if (this->animationTimer.getElapsedTime().asSeconds() >= .2f || getAnimationSwitch()) {
				this->currentFrame.top = /*animState*/ 0.f * 100.f;
				this->currentFrame.left += 50.f;
				if (this->currentFrame.left >= 250.f) {
					this->currentFrame.left = 0;
				}
				this->spriteComponent->SetFrame(this->currentFrame);
			}
			else {
				this->animationTimer.restart();
			}
		}
	}

	const bool& getAnimationSwitch() {
		bool anim_switch = this->animationSwitch;
		if (this->animationSwitch)
			this->animationSwitch = false;
		return anim_switch;
	}

	void resetAnimationTimer() {
		this->animationTimer.restart();
		this->animationSwitch = true;
	}

	void setAnimationState(ANIMATION_STATES state) {
		this->animState = state;

		switch (state)
		{
		case IDLE:
			break;
		case MOVING_LEFT:
			std::cout << "LEFT" << this->spriteComponent->GetSprite().getScale().x << std::endl;
			this->spriteComponent->SetScale(-1.f, 1.f);
			this->spriteComponent->SetOrigin(this->spriteComponent->GetSprite().getGlobalBounds().width, 0.f);
			break;
		case MOVING_RIGHT:
			std::cout << "RIGHT" << this->spriteComponent->GetSprite().getScale().x << std::endl;
			this->spriteComponent->SetScale(1.f, 1.f);
			this->spriteComponent->SetOrigin(0.f, 0.f);
			break;
		case JUMPING:
			break;
		case FALLING:
			break;
		case ATTACK:
			break;
		case TAKE_DAMAGE:
			break;
		case DIE:
			break;
		default:
			break;
		}
	}
};