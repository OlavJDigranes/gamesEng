#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

using namespace sf;
using namespace std;

size_t gameWidth = 500;
size_t gameHeight = 500;

b2World* world;

vector<b2Body*> bodies;
vector<Shape*> sprites;

// 1 sfml unit = 30 physics units
const float physics_scale = 30.f;
const float physics_scale_inv = 1 / physics_scale;

// Numbers for accuracy and physics simulation
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

inline const Vector2f bv2_to_sv2(const b2Vec2& in) {
    return Vector2f(in.x * physics_scale, in.y * physics_scale);
}

inline const b2Vec2 sv2_to_bv2(const Vector2f& in) {
    return b2Vec2(in.x * physics_scale_inv, in.y * physics_scale_inv);
}

inline const Vector2f invert_height(const Vector2f& in) {
    return Vector2f(in.x, gameHeight - in.y);
}

b2Body* CreatePhysicsBox(b2World& World, const bool dynamic, const Vector2f& position, const Vector2f& size) {
    b2BodyDef BodyDef;
    BodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
    BodyDef.position = sv2_to_bv2(position);

    b2Body* body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape1;
    Shape1.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);

    b2FixtureDef FixtureDef;
    FixtureDef.density = dynamic ? 10.f : 0.f;
    FixtureDef.restitution = 1.0f;
    FixtureDef.friction = dynamic ? 0.8f : 1.0f;

    FixtureDef.shape = &Shape1;

    body->CreateFixture(&FixtureDef);
    return body;
}

b2Body* CreatePhysicsBox(b2World& world, const bool dynamic, const RectangleShape& rs) {
    return CreatePhysicsBox(world, dynamic, rs.getPosition(), rs.getSize());
}

void Init() {
    const b2Vec2 gravity(0.0f, -10.0f);
    world = new b2World(gravity);

    // Walls - top, bottom, left, right
    Vector2f walls[] = {
        Vector2f(gameWidth * 0.5f, 5.f), Vector2f(gameWidth, 10.f),
        Vector2f(gameWidth * 0.5f, gameHeight - 5.f), Vector2f(gameWidth, 10.f),
        Vector2f(5.f, gameHeight * 0.5f), Vector2f(10.f, gameHeight),
        Vector2f(gameWidth - 5.f, gameHeight * 0.5f), Vector2f(10.f, gameHeight)
    };

    for (int i = 0; i < 7; i += 2) {
        auto s = new RectangleShape();
        s->setPosition(walls[i]);
        s->setSize(walls[i + 1]);
        s->setOrigin(walls[i + 1] / 2.0f);
        s->setFillColor(Color::Red);
        sprites.push_back(s);

        auto b = CreatePhysicsBox(*world, false, *s);
        bodies.push_back(b);
    }

    for (int i = 1; i < 11; i++) {
        auto s = new RectangleShape();
        s->setPosition(Vector2f(i * gameWidth / 12.f, gameHeight * 0.7f));
        s->setSize(Vector2f(50.f, 50.f));
        s->setOrigin(Vector2f(25.f, 25.f));
        s->setFillColor(Color::White);
        sprites.push_back(s);

        auto b = CreatePhysicsBox(*world, true, *s);
        b->ApplyAngularImpulse(5.f, true);
        bodies.push_back(b);
    }
}

void Update(RenderWindow& window) {
    // Get delta time
    static Clock clock;
    float dt = clock.restart().asSeconds();

    // ESC quit
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    world->Step(dt, velocityIterations, positionIterations);

    for (int i = 0; i < bodies.size(); i++) {
        sprites[i]->setPosition(invert_height(bv2_to_sv2(bodies[i]->GetPosition())));
        sprites[i]->setRotation((180 / b2_pi) * bodies[i]->GetAngle());
    }
}

void Render(RenderWindow& window) {
    for (const auto s : sprites) {
        window.draw(*s);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "PHYSICS");
    Init();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}