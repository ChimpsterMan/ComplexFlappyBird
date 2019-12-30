#include <iostream>
#include <SFML/Graphics.hpp>

class Pipe {
public:
	
private:
	double WIDTH;
	double HEIGHT;
	double x;
	double y;
	double vX;
	double vY;

	bool visible;

	sf::Texture texture;
	sf::Sprite body;

public:
	//default
	Pipe();
	Pipe(double x, double y);

	void update(double time);
	void init();
	
	bool checkCollision(double x, double y);

	//setters
	void setPosition(double x, double y);
	void setSpeed(double v);
	void setVisibility(bool vis);
	void setX(double x);
	void setY(double y);

	//getters
	sf::Sprite getBody();

	double getX();
	double getY();
	double getWidth();
	double getHeight();
	bool isVisible();
};
