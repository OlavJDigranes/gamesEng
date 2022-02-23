/*
#include "entity.h"
#include "game.h"
#include "system_renderer.h"
#include <iostream>

using namespace std;
using namespace sf;

// EntityManager
void EntityManager::Render(sf::RenderWindow& window) {
	for (const auto& e : list) {
		e->render();
	}
}
void EntityManager::Update(double dt) {
	for (auto& e : list) {
		e->update(dt);
	}
}
*/