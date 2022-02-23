//scene.h
#pragma once
#include "ecm.h"

using namespace std;

class Scene {
	
	public:
		Scene() = default;

		virtual ~Scene() = default;
		virtual void update(double dt);
		virtual void render();
		virtual void load() = 0;
		vector<shared_ptr<Entity>>&getEnts();

	protected:
		EntityManager _ents;
};