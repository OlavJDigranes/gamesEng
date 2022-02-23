//pacman.h
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "scene.h"

using namespace std;
using namespace sf;

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	sf::Text text;
	sf::Font font;

public:
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	sf::Font font;
	void respawn();
	std::shared_ptr<Entity> player;
	std::vector<shared_ptr<Entity>> ghosts;

public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};