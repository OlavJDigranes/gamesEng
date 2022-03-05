#include "cmp_actor_movement.h"
#include "game.h"
#include "LevelSystem.h"

using namespace std;
using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {}

float ActorMovementComponent::getSpeed() const { return _speed; }

void ActorMovementComponent::setSpeed(float new_speed) { _speed = new_speed; }

bool ActorMovementComponent::validMove(const Vector2f& pos) {
	return ls::getTileAt(pos) != ls::WALL;
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

void ActorMovementComponent::move(const Vector2f& p) {
	auto pp = _parent->getPosition() + p;

	if (!validMove({ pp.x, _parent->getPosition().y })) {
		pp.x = _parent->getPosition().x;
	}
	if (!validMove({ _parent->getPosition().x, pp.y })) {
		pp.y = _parent->getPosition().y;
	}

	_parent->setPosition(pp);
}

// Player Movement Component
PlayerMovementComponent::PlayerMovementComponent(Entity* p) : ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {
	if (_parent->isAlive()) {
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

		if (_parent->getPosition().x - 15.f > 0 &&
			_parent->getPosition().x + 15.f < gameWidth &&
			_parent->getPosition().y - 15.f > 0 &&
			_parent->getPosition().y + 15.f < gameHeight) 
		{

			move(direction);
		}
		else {
			if (_parent->getPosition().x - 15.f <= 0 && direction.x < 0) {
				direction.x = 0;
			}
			else if (_parent->getPosition().x + 15.f >= gameWidth && direction.x > 0) {
				direction.x = 0;
			}
			if (_parent->getPosition().y - 15.f <= 0 && direction.y < 0) {
				direction.y = 0;
			}
			else if (_parent->getPosition().y + 15.f >= gameHeight && direction.y > 0) {
				direction.y = 0;
			}
			move(direction);
		}
	}
}