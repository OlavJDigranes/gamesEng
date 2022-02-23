#include <SFML/Graphics.hpp>
#include "entity.h"
#include "game.h"
#include "system_renderer.h"
#include "pacman.h"
#include <iostream>

using namespace sf;
using namespace std;

void Load() {
    // Load Scene-Local Assets
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->Load();
    menuScene->Load();
	
    // Start at main menu
    activeScene = menuScene;
}

void Update(RenderWindow& window) {
	// Get delta time
	static Clock clock;
	double dt = clock.restart().asSeconds();

    activeScene->Update(dt);
	//passedTime += dt;

	// ESC quit
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow& window) {
    activeScene->Render();
	// Render entities with entity manager
	Renderer::render();
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "P A C - M A N");
	Renderer::initialise(window);
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}