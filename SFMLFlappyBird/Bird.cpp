#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bird.h"

using namespace std;

Bird::Bird(int initX, int initY) {
	Bird::WIDTH = 50;
	Bird::HEIGHT = 50;
	Bird::x = 0;
	Bird::y = 0;
	Bird::rot = 0;
	Bird::wingState = GLIDE;
	Bird::thrust = 0;
	Bird::birdShape = sf::RectangleShape(sf::Vector2f(Bird::WIDTH, Bird::HEIGHT));
	Bird::birdShape.setFillColor(sf::Color::Yellow);
}

Bird::Bird() {
	Bird(0, 0);
}

//interactions
//time in millisec pls
//uses physics equations to adjust the movement of the bird based on its wing drag
//rip me I had to draw out the force diagrams.
void Bird::update(int time) {
	int vX = 0;
	int vY = 0;



	Bird::y += vY;
}

void Bird::control(Bird::wing wings) {
	if (wings == Bird::wing::DOWN) {
		thrust = 10;
	}
}

//setters
void Bird::setPosition(int x, int y) {
	Bird::x = x;
	Bird::y = y;

	birdShape.setPosition(sf::Vector2f(Bird::x, Bird::y));
}

//getters

sf::RectangleShape Bird::getShape() {
	return birdShape;
}