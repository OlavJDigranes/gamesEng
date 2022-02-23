#include <SFML/Graphics.hpp>
#include "ecm.h"
#include "game.h"
#include "system_renderer.h"
#include "pacman.h"
#include <iostream>

using namespace sf;
using namespace std;

double timePassed = 0.0; 

void Load() {
    // Load Scene-Local Assets
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();
	
    // Start at main menu
    activeScene = menuScene;
}

void Update(RenderWindow& window) {
	// Get delta time
	static Clock clock;
	double dt = clock.restart().asSeconds();

    activeScene->update(dt);
	timePassed += dt;

	// ESC quit
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
}

void Render(RenderWindow& window) {
    activeScene->render();
	Renderer::render();
}

int main(){
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PAC - MAN");
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