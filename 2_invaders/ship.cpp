//ship.cpp
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

Ship::Ship() {};
bool Invader::direction;
float Invader::speed;

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

void Ship::moveDown() {}

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(Vector2f(16.f, 16.f));;
	setPosition(pos);
}

//void Invader::Update(const float& dt) {
//	Ship::Update(dt);
//}

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			//ships[i]->move(Vector2f(0.0f, 24.0f));
			ships[i]->moveDown();
		}
	}
}

void Invader::moveDown() {
	move(Vector2f(0.0f, 24.0f));
}

// Player
Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32))) {
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
	Ship::Update(dt);

	float direction = .0f;
	if (Keyboard::isKeyPressed(Keyboard::A) && (getPosition().x > 16)) {
		direction--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && (getPosition().x < gameWidth - 16)) {
		direction++;
	}

	move(Vector2f(direction * 300.f * dt, 0));
}