#include "scene_level2.h"
#include "../components/cmp_enemy_ai.h"
#include "../components/cmp_enemy_turret.h"
#include "../components/cmp_hurt_player.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../game.h"
#include <LevelSystem.h>
#include <iostream>
using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
void Level2Scene::Load() {
    cout << "Scene 2 Load" << endl;
    ls::loadLevelFile("res/levels/level_2.txt", 40.0f);
    auto ho = Engine::getWindowSize().y - (ls::getHeight() * 40.f);
    ls::setOffset(Vector2f(0, ho));

    // Create player
    {
        // *********************************

        player = makeEntity();
        player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
        auto s = player->addComponent<ShapeComponent>();
        s->setShape<sf::RectangleShape>(Vector2f(20.f, 30.f));
        s->getShape().setFillColor(Color::Magenta);
        s->getShape().setOrigin(Vector2f(10.f, 15.f));

        // *********************************

        player->addTag("player");
        player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 30.f));
    }

    // Create Enemy
    {
        auto enemy = makeEntity();
        enemy->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY)[0]) +
            Vector2f(0, 24));
        // *********************************
    // Add HurtComponent
        auto hurtComp = enemy->addComponent<HurtComponent>();
        // Add ShapeComponent, Red 16.f Circle
        auto shapeComp = enemy->addComponent<ShapeComponent>();
        shapeComp->setShape<sf::CircleShape>(16.f);
        shapeComp->getShape().setFillColor(Color::Red);
        shapeComp->getShape().setOrigin(Vector2f(8.f, 8.f));

        // Add EnemyAIComponent
        auto enemyAIComp = enemy->addComponent<EnemyAIComponent>();
        // *********************************
    }

    // Create Turret
    {
        auto turret = makeEntity();
        turret->setPosition(ls::getTilePosition(ls::findTiles('t')[0]) +
        //turret->setPosition(ls::getTilePosition(ls::findTiles(ls::TURRET)[0]) +
            Vector2f(20, 0));
        auto s = turret->addComponent<ShapeComponent>();
        s->setShape<sf::CircleShape>(16.f, 3);
        s->getShape().setFillColor(Color::Red);
        s->getShape().setOrigin(Vector2f(16.f, 16.f));
        turret->addComponent<EnemyTurretComponent>();
    }

    // Add physics colliders to level tiles.
    {
        // *********************************

        auto wallzes = ls::findTiles(ls::WALL);
        for (auto w : wallzes) {
            auto posw = ls::getTilePosition(w);
            posw += Vector2f(20.f, 20.f);
            auto me = makeEntity();
            me->setPosition(posw);
            me->addComponent<PhysicsComponent>(false, Vector2f(40.f, 40.f));
        }

        // *********************************
    }

    cout << " Scene 2 Load Done" << endl;
    setLoaded(true);
}

void Level2Scene::UnLoad() {
    cout << "Scene 2 UnLoad" << endl;
    player.reset();
    ls::unload();
    Scene::UnLoad();
}

void Level2Scene::Update(const double& dt) {
    Scene::Update(dt);
    const auto pp = player->getPosition();
    if (ls::getTileAt(pp) == ls::END) {
        Engine::ChangeScene((Scene*)&level3);
    }
    else if (!player->isAlive()) {
        Engine::ChangeScene((Scene*)&level2);
    }
}

void Level2Scene::Render() {
    //ls::Render(Engine::GetWindow());
    ls::render(Engine::GetWindow());
    Scene::Render();
}
