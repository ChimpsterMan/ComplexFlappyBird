#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Button {
private:
	sf::Text text;
	sf::Font font;
	sf::RectangleShape box;

public:
	Button();
	Button(string text, sf::Color color, int textSize, double x, double y, double width, double height);

	sf::Text getText();
	sf::RectangleShape getBox();
};