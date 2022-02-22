#include <SFML/Graphics.hpp>
#include "entity.h"
#include "game.h"
#include "system_renderer.h"
#include "pacman.h"
#include <iostream>

using namespace sf;
using namespace std;

void Load() {

}

void Update(RenderWindow& window) {
	// Get delta time
	static Clock clock;
	double dt = clock.restart().asSeconds();
	passedTime += dt;

	// ESC quit
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow& window) {
	// Render entities with entity manager
	Renderer::Render();
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "P A C - M A N");
	Renderer::Intialise(window);
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}