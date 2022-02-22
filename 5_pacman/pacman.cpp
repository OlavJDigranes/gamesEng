void MenuScene::Load() {
	font.loadFromFile("res/fonts/RobotoMono-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setPosition((gameWidth * .4f) - (text.getLocalBounds().width * .4f), 0);
}