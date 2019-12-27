#include <iostream>
#include <SFML/Graphics.hpp>

class Bird {
public:
	enum class wing { GLIDE, UP, DOWN };
	enum class FlightMode { ORIGINAL, EXPERIMENTAL };

private:

	int WIDTH;
	int HEIGHT;
	int thrust;
	FlightMode mode;
	wing wingState;
	double WING_RESISTANCE;
	double TOP_WING_RESISTANCE;
	double time;
	double x;
	double y;
	double vX;
	double vY;
	double rot;

	sf::Texture img;
	sf::Sprite body;

public:
	Bird(int initX, int initY);
	Bird();

	//interactions
	//the call in the main loop
	void update(double time);
	void originalControl();
	void experimentalControl(wing wings);
	void rotate(int angle);

	//physics
	//takes in pointers
	//normal flappy bird physics
	void originalPhysics(double time, double* vX, double* vY);
	//glider and complicated
	void experimentalPhysics(double time, double* vX, double* vY);

	//setters
	void setPosition(int x, int y);
	void setX(double x);
	void setY(double y);

	//getters
	sf::Sprite getBody();
	double getX();
	double getY();
	double getWidth();
	double getHeight();

};