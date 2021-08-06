#pragma once

#include "stdafx.h"
#include "Components.h"
#include "Game.h"

enum ANIMATION_STATES { 
	IDLE = 0,
	MOVING_LEFT, 
	MOVING_RIGHT, 
	JUMPING, 
	FALLING, 
	ATTACK, 
	TAKE_DAMAGE, 
	DIE, 
	POINT_ERROR, 
	POINT_OK,
	PUERTA_CERRADA,
	PUERTA_ABRIENDO,
	PUERTA_ABIERTA
};

struct AnimationSetting {
public:
	ANIMATION_STATES animationState;
	short framePositionY;
	short framesLength;
};

class AnimatorComponent : public Component {
private:
	short animState;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	bool animationSwitch;

	float animationFrameTime;

	std::vector<AnimationSetting> animationSettings;
	int spriteRectX;
	int spriteRectY;

	int animationOffsetX = -39.f;
	int animationOffsetY = -14.f;

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
		animationFrameTime = 0.f;
		if (!entity->hasComponents<SpriteComponent>()) {
			entity->addComponent<SpriteComponent>();
		}
		spriteComponent = &entity->getComponent<SpriteComponent>();
		this->animationActive = false;
		this->animationTimer.restart();
		this->animationSwitch = true;

		//if (spriteRectX <= 0) {
		//	spriteRectX = 50;
		//}

		//if (spriteRectY <= 0) {
		//	spriteRectY = 50;
		//}


		//TODO: Define the sheet tile
		this->currentFrame = sf::IntRect(0, 0, spriteRectX, spriteRectY);
	}

	void updateDeltaTime(const float& dt) {
		this->animationFrameTime += dt;
	}
	
	void update() override {
		if (spriteComponent != nullptr) {
			if (this->animationFrameTime > 0.025f) { //  || getAnimationSwitch()) {
				this->animationFrameTime = 0.f;
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

					if (this->animState == ANIMATION_STATES::PUERTA_ABRIENDO) {
						this->currentFrame.left = 40 * spriteRectX;
						animationActive = false;
					}

					this->animationActive = false;
					// Check for animations ends
			
				}
				this->spriteComponent->SetFrame(this->currentFrame);
			}
			else {
				if (this->animState != ANIMATION_STATES::DIE) {
					this->animationTimer.restart();
				}
			}
			this->spriteComponent->SetSpritePosition(animationOffsetX, animationOffsetY);
		}
	}

	void AddAnimationSetting(AnimationSetting animationData) {
		//std::cout << "Pushed animationSettings" << std::endl;
		this->animationSettings.push_back(animationData);
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
		int animationSettingIndex = 0;
		for (size_t i = 0; i < animationSettings.size(); i++)
		{
			if (this->animationSettings[i].animationState == state) {
				animationSettingIndex = i;
				this->maxFrameOfAnimation = animationSettings[animationSettingIndex].framesLength * this->spriteRectX;
				this->animationIndex = animationSettings[animationSettingIndex].framePositionY;
				if (animationSettings[animationSettingIndex].animationState == MOVING_LEFT) {
					this->spriteComponent->SetScale(-1.f, 1.f);
					this->spriteComponent->SetOrigin(this->spriteComponent->GetSprite().getGlobalBounds().width, 0.f);
				}
				else if (animationSettings[animationSettingIndex].animationState == MOVING_RIGHT) {
					this->spriteComponent->SetScale(1.f, 1.f);
					this->spriteComponent->SetOrigin(0.f, 0.f);
				}

				//DebugAnimations(animationSettings[animationSettingIndex].animationState);
				
				if (state == ATTACK) {
					this->currentFrame.left = 0;
				}
			}
		}
	}

	void SetAnimationOffset(int xOffset, int yOffset) {
		this->animationOffsetX = xOffset;
		this->animationOffsetY = yOffset;
	}

	void DebugAnimations(ANIMATION_STATES state) {
		switch (state) {
		case IDLE:
			std::cout << "PLAYER IDLE ANIMATION" << std::endl;
			break;
		case MOVING_LEFT:
			std::cout << "PLAYER MOVE <- ANIMATION" << this->spriteComponent->GetSprite().getScale().x << std::endl;
			break;
		case MOVING_RIGHT:
			std::cout << "PLAYER MOVE -> ANIMATION" << this->spriteComponent->GetSprite().getScale().x << std::endl;
			break;
		case JUMPING:
			std::cout << "PLAYER JUMPING ANIMATION" << std::endl;
			break;
		case FALLING:
			std::cout << "PLAYER FALLING ANIMATION" << std::endl;
			this->currentFrame.left = 0;
			break;
		case ATTACK:
			std::cout << "PLAYER ATTACK ANIMATION" << std::endl;
			this->currentFrame.left = 0;
			break;
		case TAKE_DAMAGE:
			std::cout << "PLAYER TAKE_DAMAGE ANIMATION" << std::endl;
			break;
		case DIE:
			std::cout << "PLAYER DYING ANIMATION" << std::endl;
			break;
		default:
			break;
		}
	}
};