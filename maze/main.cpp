//main.cpp
#include <SFML/Graphics.hpp>

#include "player.h"

using namespace std;
using namespace sf;

const int gameWidth = 800;
const int gameHeight = 600;

Player player;

void Load() {
	
}

void Update(RenderWindow& window) {
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
