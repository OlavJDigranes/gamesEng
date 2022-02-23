#include "scene.h"

void Scene::update(double dt) {
	_ents.Update(dt);
}

void Scene::render() {
	_ents.Render();
}

vector<shared_ptr<Entity>>&Scene::getEnts() {return _ents.list;}