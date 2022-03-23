#include "cmp_actor_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include <engine.h>

using namespace sf;
using namespace std;

// Checks keyboard and moves the player.
void ActorMovementComponent::update(double dt) {
    Vector2f direction(0.0f, 0.0f);
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        direction.x -= 1.0f;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        direction.x += 1.0f;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        direction.y -= 1.0f;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        direction.y += 1.0f;
    }

    move(normalize(direction) * _speed * (float)dt);
}

// Initialises the component.
ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

// Checks if the proposed move is valid.
bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
    if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x ||
        pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y) {
        return false;
    }
    return true;
}

// Moves the component's parent.
void ActorMovementComponent::move(const sf::Vector2f& p) {
    auto new_pos = _parent->getPosition() + p;
    if (validMove(new_pos)) {
        _parent->setPosition(new_pos);
    }
}

// Moves the component's parent.
void ActorMovementComponent::move(float x, float y) {
    move(Vector2f(x, y));
}