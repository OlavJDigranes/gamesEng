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

