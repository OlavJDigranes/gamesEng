//"cmp_actor_movement.h"
#pragma once
#include <ecm.h>

class ActorMovementComponent : public Component {
protected:
    bool validMove(const sf::Vector2f&);
    float _speed;

public:
    explicit ActorMovementComponent(Entity* p);
    ActorMovementComponent() = delete;

    float getSpeed() const;
    void setSpeed(float _speed);

    void move(const sf::Vector2f&);
    void move(float x, float y);

    void render() override {}
    void update(double dt) override;
};

class PlayerMovementComponent : public ActorMovementComponent {
public:
    PlayerMovementComponent(Entity* p);
    PlayerMovementComponent() = delete;
    ~PlayerMovementComponent() = default;
    void update(double dt) override;
};