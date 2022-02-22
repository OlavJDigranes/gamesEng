//pacman.h
#pragma once
#include <memory>
#include "scene.h"

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene {
private:
	Text text;
	Font font;
public:
	MenuScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};