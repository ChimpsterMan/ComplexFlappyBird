// SFMLFlappyBird.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bird.h"

sf::RenderWindow window;
const int FPS = 60;
const int WIDTH = 600;
const int HEIGHT = 600;
Bird bird = Bird();

void draw() {
	window.clear();
	window.draw(bird.getShape());
	window.display();
}

void setup() {
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Complex Flappy Bird");
	window.setFramerateLimit(1000 / FPS);
}

int main()
{
    std::cout << "Hello World!\n";
	setup();

	sf::Event event;
	while (window.isOpen()) {
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();

				return 0;
			}
		}

		draw();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
