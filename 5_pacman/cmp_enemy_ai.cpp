
#include "cmp_enemy_ai.h"
#include "LevelSystem.h"

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p), _state(ROAMING) {}

static const Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

void EnemyAIComponent::update(double dt) {
	// Amount ot move
	const auto mva = (float)(dt * _speed);
	// Current pos
	const Vector2f pos = _parent->getPosition();
	// Next position
	const Vector2f newPos = pos + _direction * mva;
	// Inverse of our current dir
	const Vector2i badDir = -1 * Vector2i(_direction);
	// Random new dir
	Vector2i newDir = directions[(rand() % 4)];

	if (_parent->isAlive()) {
		switch (_state) {
		case ROAMING:
			if (!validMove(newPos) || ls::getTileAt(pos) == ls::WAYPOINT) {
				_state = ROTATING;
			}
			else {
				move(_direction * mva);
			}
			break;

		case ROTATING:
			while (newDir == badDir || ls::getTileAt(pos + Vector2f(newDir) * ls::getTileSize()) == ls::WALL) {
				newDir = directions[(rand() % 4)];
			}
			_direction = Vector2f(newDir);
			_state = ROTATED;
			break;

		case ROTATED:
			if (ls::getTileAt(pos) != ls::WAYPOINT) {
				_state = ROAMING;
			}
			move(_direction * mva);
			break;

		default:
			break;
		}
	}
	ActorMovementComponent::update(dt);
}