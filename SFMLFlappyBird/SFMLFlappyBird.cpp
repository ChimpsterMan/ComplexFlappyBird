// SFMLFlappyBird.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Bird.h"
#include "Pipe.h"
#include "Button.h"
#include <vector>

using namespace std;

sf::RenderWindow window;
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::Sprite backgroundSprite2;

Bird bird = Bird();

Button playButton;

bool gameOver;

int stage;

const int FPS = 60;
const int WIDTH = 1200;
const int HEIGHT = 800;
const int BORDER = WIDTH * 0.7;
const double SCROLL_SPEED = 0.5;
const double PIPE_START = 0.18;
const double PIPE_END = 0.45;

vector<Pipe> pipes;

int scroll = 0;
int cooldown = 300;
int timer = 0;


double difficulty;

void moveBackground(double movement);

void drawPipes() {
	for (int i = 0; i < pipes.size(); i++) {
		window.draw(pipes[i].getBody());
	}
}

void draw() {
	window.clear();
	window.draw(backgroundSprite);
	window.draw(backgroundSprite2);
	drawPipes();
	window.draw(bird.getBody());
	window.display();
}

void drawMenu() {
	window.clear();

	moveBackground(-1);
	window.draw(backgroundSprite);
	window.draw(backgroundSprite2);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		
	}

	sf::Text title = sf::Text("Flappy Bird", font, 100);
	title.setFillColor(sf::Color::Black);
	title.setOrigin((title.getGlobalBounds().width / 2), (title.getGlobalBounds().height / 2));
	title.setPosition(WIDTH/2, HEIGHT/6);
	window.draw(title);

	window.draw(playButton.getBox());
	window.draw(playButton.getText());

	window.display();

}

void controls(Bird *b) {
	timer += 1000 / FPS;

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		(*b).rotate(2);
		cout << "rotated" << endl;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		(*b).rotate(-2);
		cout << "rotated" << endl;
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (timer >= cooldown) {
			(*b).originalControl();
			timer = 0;
		}
	}
}

void moveBackground(double movement) {
	backgroundSprite.move(movement * SCROLL_SPEED, 0);
	backgroundSprite2.setPosition(backgroundSprite.getPosition().x + WIDTH, 0);

	if (backgroundSprite.getPosition().x <= - WIDTH) {
		backgroundSprite.setPosition(0, 0);
		backgroundSprite2.setPosition(backgroundSprite.getPosition().x + WIDTH, 0);
	}
}

void createPipe() {
	Pipe pipe;
	pipe.setPosition(WIDTH + 100, -pipe.getHeight() * (double(rand() % int((PIPE_END - PIPE_START) * 100)) / 100 + PIPE_START));
	pipes.push_back(pipe);
	pipes[pipes.size() - 1].init();
}

void createPipe(int difficulty) {
	for (int i = 0; i < difficulty; i++) {
		Pipe pipe;

		/*int adjust;
		if (i > 0) { adjust = 1; }
		else { adjust = 0; }*/

		pipe.setPosition(i * (WIDTH / difficulty), -pipe.getHeight() * (double(rand() % int((PIPE_END - PIPE_START) * 100)) / 100 + PIPE_START));
		pipe.setVisibility(false);
		pipes.push_back(pipe);
		pipes[pipes.size() - 1].init();
	}
}

void pipeUpdate() {
	//run through all pipe objects in the vector pipes
	for (int i = 0; i < pipes.size(); i++) {
		//move the pipe according to its velocity and well "update" to new information based on time in milliseconds
		pipes[i].update(1);

		//check for collision with bird
		if (pipes[i].checkCollision(bird.getX() + bird.getWidth() / 2, bird.getY() + bird.getHeight() / 2)) {
			gameOver = true;
			cout << "game over" << endl;
		}
		
		//remove old pipes
		//if it goes to the left of the screen and is no longer visible
		if (pipes[i].getX() + pipes[i].getWidth() < 0) {
			pipes.erase(pipes.begin() + i);
			
			//make new replacement for pipe
			createPipe();
		}
	}
}

void sideScrollUpdate() {
	double x = bird.getX();
	double y = bird.getY();
	double rightOffset = x - (WIDTH - BORDER);
	double leftOffset = x - BORDER;

	if (rightOffset > 0) {
		bird.setX(WIDTH - BORDER);
		scroll += rightOffset;
		moveBackground(-rightOffset * SCROLL_SPEED);
	}
	/*
	else if (leftOffset < 0) {
		bird.setX(BORDER);
		scroll += leftOffset;
	}
	*/
	else {
		return;
	}

}

void setup() {
	gameOver = false;
	difficulty = 3;
	stage = 0;
	string str = "Play";
	playButton = Button(str, sf::Color::Blue, 50, WIDTH / 2, HEIGHT / 2, 200, 70);

	bird.setPosition(-100, HEIGHT / 2);

	backgroundTexture.loadFromFile("background.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite2.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
	backgroundSprite2.setPosition(backgroundSprite.getPosition().x + WIDTH, 0);
	backgroundSprite.setScale((float)WIDTH / backgroundTexture.getSize().x, (float)HEIGHT / backgroundTexture.getSize().y);
	backgroundSprite2.setScale((float)WIDTH / backgroundTexture.getSize().x, (float)HEIGHT / backgroundTexture.getSize().y);

	window.create(sf::VideoMode(WIDTH, HEIGHT), "Complex Flappy Bird");
	window.setFramerateLimit(FPS);

	createPipe(difficulty);
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

		if (stage == 0) {
			drawMenu();
		}
		else if (stage == 1) {
			controls(&bird);
			bird.update(1000 / FPS);
			pipeUpdate();
			sideScrollUpdate();
			draw();
		}
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
