//scene.h
//#include "Entity.h"
#include "ecm.h"

using namespace std;

class Scene {
	
	public:
		Scene() = default;

		virtual ~Scene() = default;
		virtual void Update(double dt);
		virtual void Render();
		virtual void Load() = 0;
		vector<shared_ptr<Entity>>& getEnts();

	protected:
		EntityManager _ents;
/*
public:
  Scene() = default;

  virtual ~Scene() = default;
  virtual void update(double dt);
  virtual void render();
  virtual void load() = 0;
  std::vector<std::shared_ptr<Entity>> &getEnts();

protected:
  EntityManager _ents;
  */

};