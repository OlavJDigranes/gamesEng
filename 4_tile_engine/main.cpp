#include <SFML/Graphics.hpp>
#include "game.h"
#include "player.h"
#include "LevelSystem.h"
#include <iostream>

using namespace sf;
using namespace std;

unique_ptr<Player> player;

void Load() {
	
	ls::loadLevelFile("res/levels/maze.txt");

	Vector2f p = ls::getStartPos(); 

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}

	player = make_unique<Player>();

	player->setPosition(p);
}

void Update(RenderWindow& window) {
	// Get delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();

	// ESC quit
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	player->Update(dt);
}

void Render(RenderWindow& window) {
	ls::Render(window);

	player->Render(window);
	
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "TILE ENGINE");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}

/*
Disallow player from moving onty tile type
	- if (tile = wall) {disallow movement}
	- if (tile = enemy) {reset player}

Set player to start tile:
	- Get tile pos as vec2f
	- set player pos to tile pos

End game
	- if (player.pos == endtile.pos) {exit game, print congrats to console}

Timer
	- start at load, end at end
*/