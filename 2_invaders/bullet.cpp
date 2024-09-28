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

void Bullet::Update(const float& dt) {
    move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));

    if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
        // Off screen - do nothing
        return;
    }
    else {
        move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));
        const FloatRect boundingBox = getGlobalBounds();

        for (auto s : ships) {
            // Use dynamic_cast to check if the ship is a Player or an Invader
         
            if (dynamic_cast<Player*>(s)) {
                // This ship is a Player
                
                if (!_mode) {
                    
                    // Player bullets don't collide with player
                    continue;
                }
            }
            else if (dynamic_cast<Invader*>(s)) {
                // This ship is an Invader
                if (_mode) {
                    // Invader bullets don't collide with other invaders
                    continue;
                }
            }

            // Check for collision with non-exploded ships
            if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
                // Explode the ship
                s->Explode();
                // Warp bullet off-screen
                setPosition(Vector2f(-100, -100));
                return;
            }
        }
    }
}


Bullet::~Bullet() {
    // Empty destructor, but needed for proper linking
}
