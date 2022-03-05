#include "cmp_pickup.h"
#include "pacman.h"
#include "maths.h"
#include "cmp_actor_movement.h"

PickupComponent::PickupComponent(Entity* p) : Component(p) {}

void PickupComponent::update(double dt) {
	
	//For every entity in the scene
	for (auto& e : activeScene->getEnts()) {

		//within 30 unit of me
		if (length(_parent->getPosition() - e->getPosition()) <= 30.f) {
			auto movementCmp = e->GetCompatibleComponent<ActorMovementComponent>(); //get teh entity AMC, if it has one 
			
			//if it has one
			if (movementCmp.size() > 0) {
				movementCmp[0]->setSpeed(movementCmp[0]->getSpeed() + _points); // speed up entity
				_parent->setForDelete(); //kill myself
				break; // stop looking
			}
		}
	}
}

float PickupComponent::getPoints() {
	return _points;
}

void PickupComponent::setPoints(float new_points) {
	_points = new_points;
}