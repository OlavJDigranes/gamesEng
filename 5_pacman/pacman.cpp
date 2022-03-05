#include "pacman.h"
#include "system_renderer.h"
#include "game.h"
#include "LevelSystem.h"
#include "ecm.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_enemy_ai.h"
#include "cmp_pickup.h"

//using namespace std;
//using namespace sf;

#define GHOSTS_COUNT 4

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

//Nibbles
vector<shared_ptr<Entity>> nibbles;

shared_ptr<Entity> makeNibble(const Vector2ul& nl, bool big) {
	auto cherry = make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();
	s->getShape().setFillColor(Color::White);
	cherry->addComponent<PickupComponent>(big);
	cherry->setPosition(ls::getTilePosition(nl) + Vector2f(10.f, 10.f));
	return cherry;
}

//Menu Scene
void MenuScene::update(double dt) {
  if (Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }
    Scene::update(dt);
    text.setString("Almost Pacman");
}

void MenuScene::render() {
  Renderer::queue(&text);
  Scene::render();
}

void MenuScene::load() {
	font.loadFromFile("res/fonts/RobotoMono-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(Vector2f((gameWidth * .4f) - (text.getLocalBounds().width * .4f), 0));
}

//Game Scene
void GameScene::load(){
	font.loadFromFile("res/fonts/RobotoMono-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition(Vector2f((gameWidth * .4f) - (text.getLocalBounds().width * .4f), 0));
	text.setString("PAC-MAN");

  // Load the level
	ls::loadLevelFile("res/levels/pacman.txt", 25.0f);

	//TODO MAY BE PROBELM HERE WITH player

	// Create player
	auto plr = make_shared<Entity>();
	auto s = plr->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(12.f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(Vector2f(12.f, 12.f));
	player->addComponent<PlayerMovementComponent>();
	_ents.list.push_back(move(plr));
	player = _ents.list[_ents.list.size()-1];
	

	// Create ghosts
	const Color ghost_cols[]{ {208, 62, 25},    // red Blinky
							  {219, 133, 28},   // orange Clyde
							  {70, 191, 238},   // cyan Inky
							  {234, 130, 229} }; // pink Pinky

	for (int i = 0; i < GHOSTS_COUNT; i++) {
		auto ghost = make_shared<Entity>();
		auto s1 = ghost->addComponent<ShapeComponent>();
		s1->setShape<sf::CircleShape>(12.f);
		s1->getShape().setFillColor(ghost_cols[i % 4]);
		s1->getShape().setOrigin(Vector2f(12.f, 12.f));
		ghost->addComponent<EnemyAIComponent>();
		_ents.list.push_back(ghost);
		ghosts.push_back(_ents.list[_ents.list.size() - 1]);
	}

	this->respawn();
}

// Game Scene
void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);

	for (auto& g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < 30.0f) {
			respawn();
		}
	}
}

//Render
void GameScene::render() {
	ls::Render(Renderer::getWindow());
	Renderer::queue(&text);
	Scene::render();
}

//Respawn function 
void GameScene::respawn() {
	player->setPosition(ls::getTileOrigin(ls::findTiles(ls::START)[0]));
	player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (auto& g : ghosts) {
		g->setPosition(ls::getTileOrigin(ghost_spawns[rand() % ghost_spawns.size()]));
		g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
	}

	//Kill nibbles
	for (auto& n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();

	//New nibbles
	auto nibblePos = LevelSystem::findTiles(LevelSystem::EMPTY);
	for (const auto& np : nibblePos) {
		auto cherry = makeNibble(np, false);
		_ents.list.push_back(cherry);
		nibbles.push_back(_ents.list[_ents.list.size() - 1]);
	}

	//New cherries
	auto nibblePos2 = LevelSystem::findTiles(LevelSystem::WAYPOINT);
	for (const auto& np2 : nibblePos2) {
		auto cherry2 = makeNibble(np2, true);
		_ents.list.push_back(cherry2);
		nibbles.push_back(_ents.list[_ents.list.size() - 1]);
	}
}
