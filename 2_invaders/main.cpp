
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;


//Main.cpp
sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship*> ships;
//const int gameWidth = 800;
//const int gameHeight = 600;


void Load() {
    if (!spritesheet.loadFromFile("res/spriteSheets/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(IntRect(Vector2(0, 0), Vector2(32, 32)));

	Invader* inv = new Invader(sf::IntRect(Vector2(0, 0), Vector2(32, 32)), { 100,100 });
	ships.push_back(inv);
}

void Update() {
	static Clock clock;
	float dt = clock.restart().asSeconds();
	for (auto& s : ships) {
		s->Update(dt);
	};
}

void Render(RenderWindow& window) {
	for (const auto s : ships) {
		window.draw(*s);
	}
	window.draw(invader);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		Update();
		Render(window);
		window.display();
	}
	return 0;
}


//NOTED LINES
//sprite.setTextureRect(IntRect(Vector2(0, 0), Vector2(32, 32)));

//
/*
int main(){

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML shapes", sf::Style::Default, settings);
  sf::CircleShape circle(10.f);
  sf::RectangleShape sqr(sf::Vector2f(200, 200));

  sqr.setSize(sf::Vector2f(150, 150));
  sqr.setFillColor(sf::Color::Cyan);
  circle.setFillColor(sf::Color::Magenta);
  circle.setRadius(20.f);
  circle.setPosition(sf::Vector2f(30, 30));

  while (window.isOpen()){
	  sf::Event event;
	  while (window.pollEvent(event)){
	  if (event.type == sf::Event::Closed){
		window.close();
	  }
	}
	window.clear();
	window.draw(sqr);
	window.draw(circle);
	window.display();
  }
  return 0;
}
*/