#pragma once
#include <SFML/Graphics.hpp>
#include "ecm.h"

using namespace std;
using namespace sf;

class PickupComponent : public Component {
protected:
	float _points = 1.f;

public:
	explicit PickupComponent(Entity* p, bool big);
	PickupComponent() = delete;
	~PickupComponent() = default;

	float getPoints();
	void setPoints(float new_points);

	void render() override; 
	void update(double dt) override;
};