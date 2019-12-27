#include <iostream>
#include <string>
#include "Button.h";

Button::Button() {

}

Button::Button(string text, sf::Color color, int textSize, double x, double y, double width, double height) {
	Button::font = sf::Font();
	if (!Button::font.loadFromFile("arial.ttf")) {

	}
	Button::text = sf::Text(text, font, textSize);
	Button::text.setOrigin(sf::Vector2f(Button::text.getGlobalBounds().width / 2, Button::text.getGlobalBounds().height / 2));
	Button::text.setPosition(sf::Vector2f(x, y));

	Button::box = sf::RectangleShape();
	box.setSize(sf::Vector2f(width,height));
	box.setOrigin(sf::Vector2f(width / 2, height / 2));
	box.setPosition(sf::Vector2f(x, y));
	box.setFillColor(color);
}

sf::Text Button::getText() {
	return Button::text;
}

sf::RectangleShape Button::getBox() {
	return Button::box;
}