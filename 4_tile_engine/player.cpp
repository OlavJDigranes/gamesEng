//player.cpp
#include "player.h"
#include <iostream>

using namespace sf;
using namespace std;

void Player::Update(double dt) {
	Vector2f direction = { 0.f, 0.f };
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction.x = -_speed * dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction.x = _speed * dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction.y = _speed * dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction.y = -_speed * dt;
	}
	move(direction);
	Entity::Update(dt);
	//cout << "____" << endl;
	//cout << direction.x << endl;
	//cout << direction.y << endl;
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(50.f, 50.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}