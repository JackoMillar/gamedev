#include <SFML/Graphics.hpp>
#include <iostream>
//main.cpp
#include "ship.h"
#include "bullet.h"
//...
std::vector<Ship*> ships;
std::vector<Ship*> playerships;
std::vector<Bullet*> bullets;

using namespace std;
using namespace sf;

const int gameWidth = 800;
const int gameHeight = 600;

const int invaders_rows = 5;
const int invaders_columns = 11;
const int invader_width = 32;
const int invader_height = 32;
const int invader_spacing_x = 40; // Horizontal spacing between invaders
const int invader_spacing_y = 40; // Vertical spacing between invaders
const int start_x = 100;  // Starting x position
const int start_y = 50;   // Starting y position

Texture spritesheet;
Sprite invader;
Sprite player;
Sprite bullet;

void Load() {
    if (!spritesheet.loadFromFile("res/sprites/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    
    auto player = new Player();
    playerships.push_back(player);

    // Initialize speed
    Invader::speed = 40.0f; // Set a desired speed value

    Player::playerSpeed = 300.f;

    int posx = 50.f;
    int posy = 50.f;
    int invx = 0;
    for (int r = 0; r < invaders_rows; ++r) {
        // Determine the row group to decide which sprite to use
        int sprite_row;
        if (r == 0) {
            sprite_row = 0;  // First row is type 0
        }
        else if (r <= 2) {
            sprite_row = 1;  // Second and third rows are type 1
        }
        else if (r <= 4) {
            sprite_row = 2;  // Fourth and fifth rows are type 2
        }

        // Adjust Y offset based on the sprite_row to select the correct texture
        auto rect = IntRect(Vector2i(sprite_row * 32, 0), Vector2i(32, 32));

        for (int c = 0; c < invaders_columns; ++c) {
            Vector2f position(posx * c, posy * r);
            auto inv = new Invader(rect, position);
            ships.push_back(inv);
        }
    }

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

    for (auto s : playerships) {
        s->Update(dt);
    };

    // Update bullets
    for (auto b : bullets) {
        b->Update(dt);
    }

}

void Render(RenderWindow& window) {
    window.draw(invader);

    for (const auto s : ships) {
        window.draw(*s);
    }
    for (const auto s : playerships) {
        window.draw(*s);
    }

    // Render bullets
    for (const auto b : bullets) {
        window.draw(*b);
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