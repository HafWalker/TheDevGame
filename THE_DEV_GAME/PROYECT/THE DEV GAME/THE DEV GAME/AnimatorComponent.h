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

	int spriteRectX;
	int spriteRectY;

	int maxFrameOfAnimation;
	int animationIndex;

	bool animationActive;
public:
	SpriteComponent* spriteComponent;

	AnimatorComponent() = default;
	AnimatorComponent(int rectX, int rectY) {
		this->spriteRectX = rectX;
		this->spriteRectY = rectY;
	}

	void init() override {
		if (!entity->hasComponents<SpriteComponent>()) {
			entity->addComponent<SpriteComponent>();
		}
		spriteComponent = &entity->getComponent<SpriteComponent>();
		this->animationActive = false;
		this->animationTimer.restart();
		this->animationSwitch = true;
		setAnimationState(ANIMATION_STATES::IDLE);

		//if (spriteRectX <= 0) {
		//	spriteRectX = 50;
		//}

		//if (spriteRectY <= 0) {
		//	spriteRectY = 50;
		//}

		setAnimationState(ANIMATION_STATES::IDLE);

		//TODO: Define the sheet tile
		this->currentFrame = sf::IntRect(0, 0, spriteRectX, spriteRectY);
	}

	void update() override {
		if (spriteComponent != nullptr) {
			if (this->animationTimer.getElapsedTime().asSeconds() >= .125f || getAnimationSwitch()) {
				this->animationActive = true;
				this->currentFrame.top = animationIndex * spriteRectY;
				this->currentFrame.left += spriteRectX;
				//std::cout << "FrameL: " << currentFrame.left << " /MaxFrames: " << maxFrameOfAnimation << " / TOP: " << currentFrame.top << std::endl;
				if (this->currentFrame.left >= maxFrameOfAnimation) {
					this->currentFrame.left = 0;

					// Hardcode Animation checks
					if (this->animState == ANIMATION_STATES::ATTACK) {
						setAnimationState(ANIMATION_STATES::IDLE);
					}

					this->animationActive = false;
					// Check for animations ends
			
				}
				this->spriteComponent->SetFrame(this->currentFrame);
			}
			else {
				this->animationTimer.restart();

			}
			this->spriteComponent->SetSpritePosition(-39.f, -14.f);
		}
	}

	const bool& getAnimationEnd(ANIMATION_STATES animationToCheck) {
		bool result = false;
		if (this->animState == animationToCheck) {
			result = animationActive;
		}
		return result;
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
			//std::cout << "PLAYER IDLE ANIMATION" << std::endl;
			this->maxFrameOfAnimation = 48 * this->spriteRectX;
			this->animationIndex = 2;
			break;
		case MOVING_LEFT:
			//std::cout << "PLAYER MOVE <- ANIMATION" << this->spriteComponent->GetSprite().getScale().x << std::endl;
			this->animationIndex = 3;
			this->spriteComponent->SetScale(-1.f, 1.f);
			this->spriteComponent->SetOrigin(this->spriteComponent->GetSprite().getGlobalBounds().width, 0.f);
			this->maxFrameOfAnimation = 15 * this->spriteRectX;
			break;
		case MOVING_RIGHT:
			//std::cout << "PLAYER MOVE -> ANIMATION" << this->spriteComponent->GetSprite().getScale().x << std::endl;
			this->animationIndex = 3;
			this->spriteComponent->SetScale(1.f, 1.f);
			this->spriteComponent->SetOrigin(0.f, 0.f);
			this->maxFrameOfAnimation = 15 * this->spriteRectX;
			break;
		case JUMPING:
			//std::cout << "PLAYER JUMPING ANIMATION" << std::endl;
			this->animationIndex = 5;
			this->maxFrameOfAnimation = 15 * this->spriteRectX;
			break;
		case FALLING:
			//std::cout << "PLAYER FALLING ANIMATION" << std::endl;
			this->currentFrame.left = 0;
			this->animationIndex = 1;
			this->maxFrameOfAnimation = 22 * this->spriteRectX;
			break;
		case ATTACK:
			//std::cout << "PLAYER ATTACK ANIMATION" << std::endl;
			this->animationIndex = 4;
			this->maxFrameOfAnimation = 31 * this->spriteRectX;
			break;
		case TAKE_DAMAGE:
			//std::cout << "PLAYER TAKE_DAMAGE ANIMATION" << std::endl;
			this->animationIndex = 6;
			this->maxFrameOfAnimation = 32 * this->spriteRectX;
			break;
		case DIE:
			//std::cout << "PLAYER DYING ANIMATION" << std::endl;
			this->animationIndex = 0;
			this->maxFrameOfAnimation = 73 * this->spriteRectX;
			break;
		default:
			break;
		}
	}
};