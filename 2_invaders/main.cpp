#include <SFML/Graphics.hpp>
#include <iostream>
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
}

void Render(RenderWindow& window) {
    window.draw(invader);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
    Load();
    while (window.isOpen()) {
        window.clear();
        Render(window);
        window.display();
    }
    return 0;
}