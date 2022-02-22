//pacman.h
#pragma once
#include <memory>
#include "scene.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	Text text;
	Font font;
public:
	MenuScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class GameScene : public Scene {
private:
  sf::Text text;
  sf::Clock scoreClock;
  void respawn();

public:
  GameScene() = default;
  void update(double dt) override;
  void render() override;
  void load() override;
};