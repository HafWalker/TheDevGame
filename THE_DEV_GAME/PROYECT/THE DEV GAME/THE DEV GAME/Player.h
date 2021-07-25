#pragma once

class Player {
private:
	sf::Sprite sprite;
	sf::RectangleShape colliderRect;
	sf::Texture textureSheet;

	// Animation
	short animState;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	bool animationSwitch;

	// Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float aceleration;
	float drag;
	float gravity;
	float velocityMaxY;

	sf::Clock jumpDecayTimer;
	bool canJump;
	bool isJumping;
	float currentJumpForce;
	float jumpForce;
	float jumpDecay;

	// Core

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initPhysics();

public:
	Player();
	virtual ~Player();

	// Accesors
	const bool& getAnimationSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect getColliderlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void setCanJump(bool var);
	void resetVelocityY();

	// Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void updateSprite();
	void render(sf::RenderTarget& taget);
};

