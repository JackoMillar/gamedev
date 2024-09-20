#include <SFML/Graphics.hpp>
#include <iostream>
//main.cpp
#include "ship.h"
//...
std::vector<Ship*> ships;
using namespace std;
using namespace sf;

const int gameWidth = 800;
const int gameHeight = 600;

Texture spritesheet;
Sprite invader;

void Load() {
    if (!spritesheet.loadFromFile("res/sprites/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));

    // Add first invader
    Invader* inv1 = new Invader(sf::IntRect(Vector2i(0, 0), Vector2i(32, 32)), { 100,100 });
    ships.push_back(inv1);

    // Add second invader (at different texture and position)
    Invader* inv2 = new Invader(sf::IntRect(Vector2i(32, 0), Vector2i(32, 32)), { 200,500 });
    ships.push_back(inv2);

    // Add third invader (different position)
    Invader* inv3 = new Invader(sf::IntRect(Vector2i(64, 0), Vector2i(32, 32)), { 300,100 });
    ships.push_back(inv3);

    // Add third invader (different position)
    Invader* inv4 = new Invader(sf::IntRect(Vector2i(96, 0), Vector2i(32, 32)), { 400,200 });
    ships.push_back(inv4);


}

void Update(RenderWindow& window) {

    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    for (auto& s : ships) {
        s->Update(dt);
    };
}

void Render(RenderWindow& window) {
    window.draw(invader);

    for (const auto s : ships) {
        window.draw(*s);
    }
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}