#include "entity.h"
#include "game.h"
#include "system_renderer.h"
#include <iostream>

using namespace std;
using namespace sf;

Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

// EntityManager
void EntityManager::Render(sf::RenderWindow& window) {
	for (const auto& e : list) {
		e->Render(window);
	}
}
void EntityManager::Update(double dt) {
	for (auto& e : list) {
		e->Update(dt);
	}
}
