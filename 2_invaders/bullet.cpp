//bullet.cpp

#include "bullet.h"
#include "game.h"


using namespace sf;
using namespace std;

Bullet::Bullet(const sf::Vector2f& pos, const bool mode) : _mode(mode) {
    setPosition(pos);  // Set the position of the bullet
    setTexture(spritesheet);  // Assign the texture
    if (_mode) {  // Player bullet
        setTextureRect(IntRect(Vector2i(32, 32), Vector2i(32, 32)));  // Adjust this to match invader bullets
    }
    else {  // Invader bullet
        setTextureRect(IntRect(Vector2i(64, 32), Vector2i(32, 32)));  // Adjust this for player bullet
    }
}
/*
void Bullet::Update(const float& dt) {
	
}*/

// Update method for Bullet
void Bullet::Update(const float& dt) {
    // Move the bullet
    move(Vector2f(0, (!_mode ? -1.0f : 1.0f) * dt * 200.0f)); // Corrected the direction of the bullet movement

    // Check if the bullet is off-screen
    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        setPosition(Vector2f(-100, -100)); // Move bullet off-screen
        return;
    }

    const FloatRect boundingBox = getGlobalBounds();

    for (auto s : ships) {
        if (dynamic_cast<Player*>(s) && _mode) { // Check for invader bullet collision
            if (s->getGlobalBounds().intersects(boundingBox)) {
                printf( "Collision detected with player!" );
                s->Explode();
                setPosition(Vector2f(-100, -100));
                return;
            }
        }
        else if (dynamic_cast<Invader*>(s) && !_mode) { // Check for player bullet collision
            if (s->getGlobalBounds().intersects(boundingBox)) {
                printf("Collision detected with invader!");
                s->Explode();
                setPosition(Vector2f(-100, -100));
                return;
            }
        }
    }
}





Bullet::~Bullet() {
    // Empty destructor, but needed for proper linking
}
