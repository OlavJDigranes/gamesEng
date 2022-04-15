//"steering.cpp"
#include "steering.h"

using namespace sf;

SteeringOutput Seek::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _target->getPosition() - _character->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}

SteeringOutput Flee::getSteering() const noexcept {
    SteeringOutput steering;
    steering.direction = _character->getPosition() - _target->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}

//SteeringOutput Arrive::getSteering() const noexcept {
//    SteeringOutput steering;
//    int radius = 3; 
//    steering.direction = _target->getPosition() - _character->getPosition();
//    steering.direction = normalize(steering.direction);
//    steering.direction; 
//}

SteeringOutput Face::getSteering() const noexcept {
    SteeringOutput steering; 
    steering.direction = _target->getPosition() - _character->getPosition(); 
    steering.direction = normalize(steering.direction);
    steering.rotation = atan2(steering.direction.x, steering.direction.y) * _maxSpeed; 
    return steering; 
}