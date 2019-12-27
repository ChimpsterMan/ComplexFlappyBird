#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pipe.h";

Pipe::Pipe() {
	WIDTH = 100;
	HEIGHT = 800;
	x = 0;
	y = 0;
	vX = -5;
	vY = 0;
	visible = true;

	//set texture and sprite
	if (!Pipe::texture.loadFromFile("pipe.png")) {
		
	}
	Pipe::body.setTexture(Pipe::texture);
	Pipe::body.setScale(8, 8);
	Pipe::body.setPosition(sf::Vector2f(Pipe::x, Pipe::y));
}

Pipe::Pipe(double x, double y) {
	WIDTH = 100;
	HEIGHT = 800;
	Pipe::x = x;
	Pipe::y = y;
	vX = -5;
	vY = 0;
	visible = true;

	//set texture and sprite
	if (!texture.loadFromFile("pipe.png")) {
		std::cout << "failed" << std::endl;
	}
	body.setTexture(texture);
	body.setScale(8, 8);
	Pipe::body.setPosition(sf::Vector2f(Pipe::x, Pipe::y));
}

void Pipe::update(double time) {
	//millisec
	time /= 1000;

	x += vX;
	y += vY;

	body.setPosition(x, y);
}

void Pipe::init() {
	if (!texture.loadFromFile("pipe.png")) {
		std::cout << "failed" << std::endl;
	}
	body.setTexture(texture);
}

bool Pipe::checkCollision(double x, double y) {
	//don't check if not visible
	if (!visible) {
		return false;
	}

	//check if its in the image
	if (this->getX() < x && this->getX() + this->getWidth() > x && this->getY() < y&& this->getY() + this->getHeight() > y) {
		//set coords to local image system
		x -= this->getX();
		y -= this->getY();

		//convert to original pixel size
		x /= this->body.getScale().x;
		y /= this->body.getScale().y;

		//test according to measurements if it is hitting the pipe or flying through the center
		if (y < 117 || y > 144) {
			return true;
		}
	}

	return false;
}

//setters
void Pipe::setPosition(double x, double y) {
	Pipe::x = x;
	Pipe::y = y;
	Pipe::body.setPosition(x, y);
}

void Pipe::setSpeed(double v) {
	Pipe::vX = v;
}

void Pipe::setVisibility(bool vis) {
	Pipe::visible = vis;
}

void Pipe::setX(double x) {
	Pipe::x = x;
}

void Pipe::setY(double y) {
	Pipe::y = y;
}

//getters
sf::Sprite Pipe::getBody() {
	if (visible) {
		return Pipe::body;
	}
	else {
		Pipe pipe(10000,10000);
		return pipe.getBody();
	}
}

double Pipe::getX() {
	return Pipe::x;
}

double Pipe::getY() {
	return Pipe::y;
}

double Pipe::getWidth() {
	return Pipe::body.getTextureRect().width * body.getScale().x;
}

double Pipe::getHeight() {
	return Pipe::body.getTextureRect().height * body.getScale().y;
}