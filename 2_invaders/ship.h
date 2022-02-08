#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ship : public sf::Sprite {
protected:
    sf::IntRect _sprite;
    //Default constructor is hidden
    Ship();
    bool _exploded = false;
    bool _player = false;
public:
    //Constructor that takes a sprite
    explicit Ship(sf::IntRect ir);
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Ship() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void Update(const float &dt);
    virtual void moveDown();
    bool is_exploded() const;
    virtual void Explode();
    bool is_player();
};

class Invader : public Ship {
public:
    Invader(sf::IntRect ir, sf::Vector2f pos);
    Invader();
    void Update(const float& dt) override;
    static bool direction;
    static float speed;
    void moveDown() override;
};

class Player : public Ship {
public:
    Player();
    void Update(const float& dt) override;
};

