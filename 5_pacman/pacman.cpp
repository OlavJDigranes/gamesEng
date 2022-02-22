#include "pacman.h"
#include "system_renderer.h"
#include "game.h"
//#include "cmp_sprite.h"
//#include "cmp_actor_movement.h"
#include "LevelSystem.h"
//#include "cmp_enemy.h"
//#include "cmp_pickup.h"

#define GHOSTS_COUNT 4

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

//Menu Scene
void MenuScene::update(double dt) {
  Scene::update(dt);
  text.setString("Almost Pacman");
}

void MenuScene::render() {
  Renderer::queue(&text);
  Scene::render();
}

void MenuScene::Load() {
	font.loadFromFile("res/fonts/RobotoMono-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition((gameWidth * .4f) - (text.getLocalBounds().width * .4f), 0);
}

//Game Scene
//Game Scene load still needed
