//"cmp_ai_steering.h"
#pragma once
#include <ecm.h>
#include "../steering.h"

class SteeringComponent : public Component {
protected:
    Seek _seek;
    Flee _flee;
    Face _face; 
    Entity* _player;
    bool validMove(const sf::Vector2f&) const;
public:
    void update(double) override;
    void move(const sf::Vector2f&, float f);
    void move(float x, float y, float f);
    void render() override { }
    explicit SteeringComponent(Entity* p, Entity* player);
    SteeringComponent() = delete;
};