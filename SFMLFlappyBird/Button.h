#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Button {
private:
	sf::Font font;
	sf::Text text;
	sf::RectangleShape box;

public:
	Button();
	Button(string text, sf::Color color, int textSize, double x, double y, double width, double height);

	bool testClick(double x, double y);

	void setFont(sf::Font font);

	sf::Text getText();
	sf::RectangleShape getBox();
};