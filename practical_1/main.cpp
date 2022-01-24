//Created for the games engineering module for Edinburgh Napier University January 2022

//This is a simple demo using provided code as a proof of concept and to test that initial setup works

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