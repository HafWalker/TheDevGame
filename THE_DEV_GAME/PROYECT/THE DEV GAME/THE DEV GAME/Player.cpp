#include "stdafx.h"
#include "Player.h"
#include "TextureManager.h"

void Player::initVariables() {
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	this->colliderRect = sf::RectangleShape(sf::Vector2f(64, 128));
	this->colliderRect.setFillColor(sf::Color::Transparent);
	this->colliderRect.setOutlineColor(sf::Color::Blue);
	this->colliderRect.setOutlineThickness(2.f);

	this->canJump = false;
}

void Player::initTexture() {
	if (!this->textureSheet.loadFromFile("D:/THE_DEV_GAME/PROYECT/Sprites/Animation/spritesheet_Full.png")) {
		std::cout << "ERROR PLAYER SHEET" << "\n";
	}
}

void Player::initSprite() {
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 128, 128);
	this->sprite.setTextureRect(currentFrame);
}

void Player::initAnimation() {
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics() {
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->aceleration = 3.f;
	this->drag = 0.80f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;

	this->jumpDecayTimer.restart();
	this->isJumping = false;
	this->currentJumpForce = 0.f;
	this->jumpForce = 25.f;
	this->jumpDecay = 1.f;
}

Player::Player() {
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
}

Player::~Player() {
}

const bool& Player::getAnimationSwitch() {
	bool anim_switch = this->animationSwitch;
	if (this->animationSwitch)
		this->animationSwitch = false;
	return anim_switch;
}

const sf::Vector2f Player::getPosition() const {
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const {
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Player::getColliderlobalBounds() const {
	return this->colliderRect.getGlobalBounds();
}

void Player::setPosition(const float x, const float y) {
	this->sprite.setPosition(x,y);
	this->colliderRect.setPosition(x, y);
}

void Player::setCanJump(bool var) {
	this->canJump = var;
}

void Player::resetVelocityY() {
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer() {
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y) {
	// Aceleration
	this->velocity.x += dir_x * this->aceleration;
	//this->velocity.x += dir_x * this->aceleration; // Gravity

	// Limit Velocity
	if (std::abs(this->velocity.x) > this->velocityMax) {
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics() {
	// Gravity
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.y) > this->velocityMaxY) {
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	// Deceleration
	this->velocity *= this->drag;

	//Limit deceleration
	if (std::abs(this->velocity.x) < this->velocityMin) {
		this->velocity.x = 0;
	}
	if (std::abs(this->velocity.y) < this->velocityMin) {
		this->velocity.y = 0;
	}
}

// MANAGE THE PLAYER MOVEMENT 
void Player::updateMovement() {
	this->animState = IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->move(-5.f,0.f);
		this->animState = MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->move(5.f, 0.f);
		this->animState = MOVING_RIGHT;
	}

	// Pass the movement to the elements
	this->sprite.move(this->velocity);
	this->colliderRect.move(this->velocity);

	// Jumping Code

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isJumping && canJump) {
		this->currentJumpForce = this->jumpForce;
		isJumping = true;
	}

	if (isJumping) {
		this->sprite.move(0.f, -currentJumpForce);
		this->colliderRect.move(0.f, -currentJumpForce);
		this->currentJumpForce -= jumpDecay;
		if (canJump) {
			if (this->jumpDecayTimer.getElapsedTime().asSeconds() >= 0.1f) {
				this->jumpDecayTimer.restart();
			}
		}
		else {
			currentJumpForce = 0.f;
		}

		if (this->currentJumpForce <= 0.1f && this->velocity.y == 0.f) {
			currentJumpForce = 0.f;
			isJumping = false;
		}
	}

	// End of Jumping Code
}

void Player::updateAnimations() {
	if (this->animState == IDLE) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.025f || this->getAnimationSwitch()) {
			this->currentFrame.top = 128.f;
			//this->currentFrame.left += 128.f; /// Fix IDLE Animation
			if (this->currentFrame.left >= 6272.f) {
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == MOVING_RIGHT) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.025f) {
			this->currentFrame.top = 258.f;
			this->currentFrame.left += 128.f;
			if (this->currentFrame.left >= 1920.f-49.f) {
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setOrigin(0.f, 0.f);

		this->sprite.setScale(1.f, 1.f);
		this->colliderRect.setOrigin(0.f, 0.f);
	}
	else if (this->animState == MOVING_LEFT) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.025f) {
			this->currentFrame.top = 258.f;
			this->currentFrame.left += 128.f;
			if (this->currentFrame.left >= 1920.f - 49.f) {
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-1.f, 1.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width, 0.f);

		this->colliderRect.setScale(-1.f, 1.f);
		this->colliderRect.setOrigin(this->colliderRect.getGlobalBounds().width, 0.f);
	}
	else
		this->animationTimer.restart();
}

void Player::update() {
	this->updateMovement();
	this->updateSprite();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::updateSprite() {
	//sf::Vector2f colliderPivot = sf::Vector2f((colliderRect.getPosition().x - (colliderRect.getGlobalBounds().width / 2)), (colliderRect.getPosition().y - colliderRect.getGlobalBounds().height));
	//this->sprite.setPosition(colliderPivot);
}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
	target.draw(this->colliderRect);
}