#include <iostream>
#include <string>
#include "Button.h";

Button::Button() {

}

Button::Button(string text, sf::Color color, int textSize, double x, double y, double width, double height) {
	if (!Button::font.loadFromFile("arial.ttf")) {
		cout << "error loading" << endl;
		system("pause");
	}
	
	Button::text.setFont(Button::font);
	Button::text.setString(text);
	Button::text.setCharacterSize(textSize);
	Button::text.setOrigin(sf::Vector2f(Button::text.getLocalBounds().width / 2, Button::text.getLocalBounds().height / 2));
	Button::text.setPosition(sf::Vector2f(x, y - height / (textSize / 10)));

	Button::box = sf::RectangleShape();
	box.setSize(sf::Vector2f(width,height));
	box.setOrigin(sf::Vector2f(width / 2, height / 2));
	box.setPosition(sf::Vector2f(x, y));
	box.setFillColor(color);
}
bool Button::testClick(double x, double y) {
	if (x >= Button::box.getPosition().x - Button::box.getSize().x / 2 && x <= Button::box.getPosition().x + Button::box.getSize().x / 2) {
		if (y >= Button::box.getPosition().y - Button::box.getSize().y / 2 && y <= Button::box.getPosition().y + Button::box.getSize().y / 2) {
			return true;
		}
	}
	return false;
}

void Button::setFont(sf::Font font) {
	Button::text.setFont(font);
}

sf::Text Button::getText() {
	return Button::text;
}

sf::RectangleShape Button::getBox() {
	return Button::box;
}