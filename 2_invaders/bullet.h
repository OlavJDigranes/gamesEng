#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	void Update(const float& dt);
	Bullet(const sf::Vector2f& pos, const bool mode);
	~Bullet() = default;
protected:
	Bullet();
	//false=player bullet, true=Enemy bullet
	bool _mode;
};

//#pragma once
//#include <SFML/Graphics.hpp>
//
//using namespace sf;
//
//class Bullet : public Sprite {
//public:
//	~Bullet() = default;
//	static void Update(const float& dt);
//	static void Render(RenderWindow& window);
//	static void Fire(const Vector2f& pos, const bool mode);
//protected:
//	Bullet();
//	bool _mode;
//	static unsigned char bulletPointer;
//	static Bullet bullets[256];
//	void _Update(const float& dt);
//};