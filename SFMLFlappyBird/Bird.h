#include <iostream>
#include <SFML/Graphics.hpp>

class Bird {
public:
	enum wing { GLIDE, UP, DOWN };
	wing wingState;
private:
	int WIDTH;
	int HEIGHT;
	int x;
	int y;
	int thrust;
	int rot;

	sf::RectangleShape birdShape;

public:
	Bird(int initX, int initY);
	Bird();

	//interactions
	void update(int time);
	void control(wing wings);

	//setters
	void setPosition(int x, int y);

	//getters
	sf::RectangleShape getShape();
};