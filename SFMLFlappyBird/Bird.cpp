#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bird.h"

using namespace std;

#define PI 3.14159
const int VIEW_SCALE = 1;

Bird::Bird() {
	Bird::WIDTH = 100 / VIEW_SCALE;
	Bird::HEIGHT = 25 / VIEW_SCALE;
	Bird::mode = Bird::FlightMode::ORIGINAL;
	Bird::time = 0;
	Bird::x = 300;
	Bird::y = HEIGHT / 2;
	Bird::vX = 0;
	Bird::vY = 0;
	Bird::rot = 0;

	//experimental
	Bird::WING_RESISTANCE = 0.2;
	Bird::TOP_WING_RESISTANCE = Bird::WING_RESISTANCE / 10;
	Bird::wingState = Bird::wing::GLIDE;
	Bird::thrust = 10;

	//set textures
	if (!Bird::img.loadFromFile("bird.png")) {
		cout << "failed" << endl;
	}
	Bird::body.setTexture(Bird::img);
	Bird::body.setScale(0.3, 0.3);
	Bird::body.setOrigin(Bird::WIDTH / 2, Bird::HEIGHT / 2);
	Bird::body.setPosition(sf::Vector2f(Bird::x, Bird::y));
}

//interactions
//time in millisec pls
//uses physics equations to adjust the movement of the bird based on its wing drag
//rip me I had to draw out the force diagrams.
void Bird::update(double time) {
	time /= 1000;
	Bird::time += time;

	if (Bird::mode == Bird::FlightMode::ORIGINAL) {
		originalPhysics(time, &(Bird::vX), &(Bird::vY));
	}
	else if (Bird::mode == Bird::FlightMode::EXPERIMENTAL) {
		experimentalPhysics(time, &(Bird::vX), &(Bird::vY));
	}

	//apply velocity changes to x and y
	Bird::y += Bird::vY;
	Bird::x += Bird::vX;

	//realize the shapes
	body.setPosition(sf::Vector2f(Bird::x / VIEW_SCALE, Bird::y / VIEW_SCALE));
	Bird::body.setRotation(360 - Bird::rot);
}

void Bird::originalControl() {
	//add vY
	Bird::vY = -8;
}

void Bird::experimentalControl(Bird::wing wings) {
	//thrust
	Bird::vX += cos(2 * PI - Bird::rot * (PI / 180)) * thrust;
	Bird::vY += sin(2 * PI - Bird::rot * (PI / 180)) * thrust;
}

//input angle change
void Bird::rotate(int angle) {
	Bird::rot += angle;
	if (Bird::rot < 0) {
		Bird::rot += 360;
	}
	Bird::rot = int(Bird::rot) % 360;
	//angle limiter
	if (Bird::rot > 90 && Bird::rot < 180) {
		Bird::rot = 90;
	}
	if (Bird::rot > 180 && Bird::rot < 270) {
		Bird::rot = 270;
	}
}

//physics
void Bird::originalPhysics(double time, double *vX, double *vY) {
	//apply gravity
	//10 is normal real world
	double gravity = 20 * time;
	*vY += gravity;

	//constant x velocity
	*vX = 5;

	//rotate as its falling
}

void Bird::experimentalPhysics(double time, double* vX, double* vY) {
	//gravity
	//add the change in gravity rather than the whole gravity equation again.
	//double gravity = 16 * Bird::time * Bird::time + Bird::vY * Bird::time - (16 * (Bird::time - time) * (Bird::time - time) + Bird::vY * (Bird::time - time));
	double gravity = 10 * time;
	Bird::vY += gravity;

	//to keep track of old position for comparisons
	double oldVX = Bird::vX;
	double oldVY = Bird::vY;

	//limiter


	//wing physics

	//lift equation
	double lift = 1 * (23.5 / 34.05) * (Bird::vX * Bird::vX + Bird::vY * Bird::vY) * 0.5 * 1 * 0.01;
	Bird::vX -= lift * sin(Bird::rot * (PI / 180));
	Bird::vY -= lift * cos(Bird::rot * (PI / 180));

	/*
	//r is the rotation value for each quadrant
	int r = 0;
	//horizontal vX reflection
	//Q1
	if (Bird::rot > 270 && Bird::rot < 315) {
		//refrence angle equation
		r = 2 * (90 - (360 - x));

		//account for the top of the wing hitting
		double wr;
		if (Bird::vX >= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = WING_RESISTANCE;
		}

		Bird::vY += Bird::vX * sin((r) * (PI / 180)) * wr;
		Bird::vX += Bird::vX * cos((r) * (PI / 180)) * wr;
	}
	//Q2
	if (Bird::rot > 315 && Bird::rot < 360) {
		//r = 90 - (2 * (90 - (360 - Bird::rot)) - 90);
		r = 2 * (90 - (360 - x));

		//account for the top of the wing hitting
		double wr;
		if (Bird::vX >= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = WING_RESISTANCE;
		}

		Bird::vY += Bird::vX * sin((r) * (PI / 180)) * wr;
		Bird::vX -= Bird::vX * cos((r) * (PI / 180)) * wr;
	}
	//Q3
	if (Bird::rot > 0 && Bird::rot < 45) {
		//r = 90 - (2 * (90 - Bird::rot) - 90);
		r = 2 * (90 - Bird::rot);

		//account for the top of the wing hitting
		double wr;
		if (Bird::vX <= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = WING_RESISTANCE;
		}

		Bird::vY -= Bird::vX * sin((r) * (PI / 180)) * wr;
		Bird::vX += Bird::vX * cos((r) * (PI / 180)) * wr;
	}
	//Q4
	if (Bird::rot > 45 && Bird::rot < 90) {
		r = 2 * (90 - Bird::rot);

		//account for the top of the wing hitting
		double wr;
		if (Bird::vX <= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = WING_RESISTANCE;
		}

		Bird::vY -= Bird::vX * sin((r) * (PI / 180)) * wr;
		Bird::vX -= Bird::vX * cos((r) * (PI / 180)) * wr;
	}
	//looking 90 deg or 270
	if (Bird::rot == 90 || Bird::rot == 270) {
		//Bird::vX -= Bird::vX * WING_RESISTANCE;
	}


	//vertical reflection
	//Q1
	if (Bird::rot > 45 && Bird::rot < 90) {
		//r = 2 * (90 - Bird::rot) - 90;
		r = (90 - Bird::rot) - Bird::rot;

		//account for the top of the wing hitting
		double wr;
		if (Bird::vY >= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = WING_RESISTANCE;
		}

		Bird::vX -= Bird::vY * cos((r) * (PI / 180)) * wr * 0.25;
		Bird::vY += Bird::vY * sin((r) * (PI / 180)) * wr;
	}
	//Q2
	if (Bird::rot > 270 && Bird::rot < 315) {
		//r = 2 * (90 - (90 - (360 - Bird::rot)))-90;
		r = 90 - 2 * (90 - (90 - (360 - Bird::rot)));

		//account for the top of the wing hitting
		double wr;
		if (Bird::vY >= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = Bird::WING_RESISTANCE;
		}

		Bird::vX += Bird::vY * cos((r) * (PI / 180)) * wr * 0.25;
		Bird::vY += Bird::vY * sin((r) * (PI / 180)) * wr;
	}
	//Q3
	if (Bird::rot > 315 && Bird::rot < 360) {
		r = 90 - 2 * (90 - (90 - (360 - Bird::rot)));

		//account for the top of the wing hitting
		double wr;
		if (Bird::vY >= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = Bird::WING_RESISTANCE;
		}

		Bird::vX += Bird::vY * cos((r) * (PI / 180)) * wr;
		Bird::vY -= Bird::vY * sin((r) * (PI / 180)) * wr;
	}
	//Q4
	if (Bird::rot > 0 && Bird::rot < 45) {
		r = (90 - Bird::rot) - Bird::rot;

		//account for the top of the wing hitting
		double wr;
		if (Bird::vY >= 0) {
			wr = Bird::TOP_WING_RESISTANCE;
		}
		else {
			wr = Bird::WING_RESISTANCE;
		}

		Bird::vX -= Bird::vY * cos((r) * (PI / 180)) * wr;
		Bird::vY -= Bird::vY * sin((r) * (PI / 180)) * wr;
	}
	//looking straight
	if (Bird::rot == 0) {
		Bird::vY -= Bird::vY * Bird::WING_RESISTANCE;
	}
	*/
}

//setters
void Bird::setPosition(int x, int y) {
	Bird::x = x;
	Bird::y = y;
}

void Bird::setX(double x) {
	Bird::x = x;
}

void Bird::setY(double y) {
	Bird::y = y;
}

//getters

sf::Sprite Bird::getBody() {
	return Bird::body;
}

double Bird::getX() {
	return Bird::x;
}

double Bird::getY() {
	return Bird::y;
}

double Bird::getWidth() {
	return Bird::body.getTextureRect().width * body.getScale().x;
}

double Bird::getHeight() {
	return Bird::body.getTextureRect().height * body.getScale().y;
}