//main.cpp
#include <SFML/Graphics.hpp>

#include "player.h"

using namespace std;
using namespace sf;

Player player;

const int gameWidth = 800;
const int gameHeight = 600;


void Load() {
	// Set player to middle of the screen
	player.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));
}

void WindowConstraints() {

	// Check player wall Collison
	const float cy = player.getPosition().y;
	const float cx = player.getPosition().x;
	if (cy > gameHeight - 25) { //bottom wall
		player.move(Vector2f(0.f, -1.f));
	}
	else if (cy < 25) { //top wall
		player.move(Vector2f(0.f, 1.f));
	}

	if (cx > gameWidth - 25) { //right wall
		player.move(Vector2f(-1.f, 0.f));
	}
	else if (cx < 25) { //left wall
		player.move(Vector2f(1.f, 0.f));
	}

}

void Update(RenderWindow& window) {

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	// Ensure the Player does not leave the boundaries of the Window
	WindowConstraints();

	player.Update(dt);
}

void Render(RenderWindow& window) {
	player.Render(window);
}



int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "ESCAPE THE MAZE");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
