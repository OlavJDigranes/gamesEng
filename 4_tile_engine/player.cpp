//player.cpp
#include "player.h"
#include "LevelSystem.h"
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
	cout << "____" << endl;
	cout << direction.x << endl;
	cout << direction.y << endl;
}

//bool validmove(Vector2f pos) {
//	return (ls::getTileAt(pos) != ls::WALL);
//}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(20.f, 20.f));
    //_shape->setOrigin(ls::getTilePosition());
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}