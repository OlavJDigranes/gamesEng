#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::W,
	Keyboard::S,
	Keyboard::Up,
	Keyboard::Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
//const float paddleSpeed = 1.f;
Vector2f ballVelocity;
bool server = false;
const float borderSpace = 10.f;
Font font;
Text text;
int p1Score = 0;
int p2Score = 0;

CircleShape ball;
RectangleShape paddles[2];

void Load() {
	// Load score boards
	font.loadFromFile("res/fonts/RobotoMono-Bold.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("0 | 0");
	text.setPosition(Vector2f((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0));

	// Setup the paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.0f);
	}
	// Setup the ball
	ball.setRadius(ballRadius);
	ball.setOrigin(Vector2f(ballRadius / 2, ballRadius / 2));
	ballVelocity = { (server ? 100.f : -100.f), 60.f };

	// Reset paddle position
	paddles[0].setPosition(Vector2f(borderSpace + paddleSize.x / 2, gameHeight / 2));
	paddles[1].setPosition(Vector2f(gameWidth - borderSpace - paddleSize.x / 2, gameHeight / 2));
	// Reset the ball position
	ball.setPosition(Vector2f(gameWidth / 2, gameHeight / 2));
}

void Reset(int loser) {
	// Initial velocity for the ball
	ballVelocity = { (server ? 100.f : -100.f), 60.f };
	// Reset paddle position
	paddles[0].setPosition(Vector2f(10 + paddleSize.x / 2, gameHeight / 2));
	paddles[1].setPosition(Vector2f(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2));
	// Reset the ball position
	ball.setPosition(Vector2f(gameWidth / 2, gameHeight / 2));
	// Setup scores
	string newScore;
	if (loser == 2) {
		p1Score++;
	}
	else {
		p2Score++;
	}
	newScore = to_string(p1Score) + " | " + to_string(p2Score);
	text.setString(newScore);
	text.setPosition(Vector2f((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0));
}

void Update(RenderWindow& window) {
	// Get delta time
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	// ESC quit
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// Handle paddle 1 movement
	float direction1 = .0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction1--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction1++;
	}
	float direction2 = .0f;
	paddles[0].move(Vector2f(0, direction1 * paddleSpeed * dt));

	// Handle paddle 2 movement
	//Make this AI:
	//Use dir2 = ball.getPos.y * dt
	
	if (Keyboard::isKeyPressed(controls[2])) {
		direction2--;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction2++;
	}

	// Collisions check
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	std::cout << by << endl;

	//if (by >= paddles[1].getPosition().y - (paddleSize.y * 0.5)) {
	//	direction2++;
	//}

	//if (by <= paddles[1].getPosition().y + (paddleSize.y * 0.5)) {
	//	direction2--;
	//}

	//direction2 = by;
	paddles[1].move(Vector2f(0, (direction2) * paddleSpeed * dt));

	// Handle ball movement
	ball.move(ballVelocity * dt);

	
	// Bottom wall
	if (by > gameHeight) {
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(Vector2f(0, -10));
	}

	// Top wall
	else if (by < 0) {
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(Vector2f(0, 10));
	}

	// Right wall
	else if (bx > gameWidth) {
		Reset(2);
	}

	// Left wall
	else if (bx < 0) {
		Reset(1);
	}

	// Left paddle collision
	else if (bx <= paddleSize.x + borderSpace &&
	//else if (bx <= paddleSize.x &&
		by >= paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		by <= paddles[0].getPosition().y + (paddleSize.y * 0.5)) 
	{
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(Vector2f(0, 10));
	}

	// Right paddle collision
	else if (bx >= (-1.5f * paddleSize.x - borderSpace + gameWidth) &&
	//else if (bx >= (-1.5f * paddleSize.x + gameWidth) &&
		by >= paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		by <= paddles[1].getPosition().y + (paddleSize.y * 0.5)) 
	{
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(Vector2f(0, -10));
	}
}

void Render(RenderWindow& window) {
	// Draw
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}

//Created for the games engineering module for Edinburgh Napier University January 2022

//This is a simple demo using provided code as a proof of concept and to test that initial setup works

/*
#include <SFML/Graphics.hpp>

int main(){

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML shapes", sf::Style::Default, settings);
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
