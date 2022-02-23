//"cmp_sprite.h"
#pragma once
#include <SFML/Graphics.hpp>
#include "ecm.h"

using namespace std;
using namespace sf;

class ShapeComponent : public Component {
protected:
	shared_ptr<Shape> _shape;

public:
	ShapeComponent();
	explicit ShapeComponent(Entity *p);

	void update(double dt) override;
	void render() override;

	Shape &getShape() const;

	template <typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};