#pragma once
#include <SFML/Graphics.hpp>
#include "ecm.h"

using namespace std;
using namespace sf;

class PickupComponent : public Component {
protected:
	float _points = 1.f;

public:
	explicit PickupComponent(Entity* p);
	PickupComponent() = delete;
	~PickupComponent() = default;

	float getPoints();
	void setPoints(float new_points);

	void Render() {}
	void update(double dt) override;
};