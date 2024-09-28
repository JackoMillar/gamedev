#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

// Constructor for Ship class
Ship::Ship() {}

// Static variables for Invader
bool Invader::direction;
float Invader::speed;

// Static variables for Player (if needed)
bool Player::playerDirection;
float Player::playerSpeed;

// Constructor for Ship with IntRect
Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
}

// Define the ship destructor (pure virtual)
Ship::~Ship() = default;

// Empty Ship Update (you can keep this or remove it if not needed)
void Ship::Update(const float& dt) {}

void Ship::Explode() {
	setTextureRect(IntRect(Vector2i(128, 32), Vector2i(32, 32)));
	_exploded = true;
}

bool Ship::is_exploded() const {
	return _exploded;
}

// Invader class constructors
Invader::Invader() : Ship() {}
Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(Vector2f(16.f, 16.f));
	setPosition(pos);
}

// Invader-specific Update method
void Invader::Update(const float& dt) {
	// Invader movement logic
	move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

	// Switch direction if invaders reach screen bounds
	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16)) {
		direction = !direction;
		// Move all invaders down when changing direction
		for (int i = 0; i < ships.size(); ++i) {
			if (dynamic_cast<Invader*>(ships[i])) {  // Only move invaders
				ships[i]->move(Vector2f(0.0f, 24.0f));
			}
		}
	}
}

// Player class constructor
Player::Player() : Ship(IntRect(Vector2i(160, 32), Vector2i(32, 32))) {
	setPosition({ gameWidth * .5f, gameHeight - 32.f });
	setOrigin(Vector2f(16.f, 16.f));  // Set the origin to the center of the sprite
}

// Player-specific Update method
void Player::Update(const float& dt) {

	static float firetime = 0.0f;
	firetime -= dt;

	// Custom movement logic for the player

	// Move left (A key) or right (D key)
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		move(Vector2f(-playerSpeed * dt, 0.0f)); // Move left
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		move(Vector2f(playerSpeed * dt, 0.0f));  // Move right
	}
	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
		sf::Vector2f bulletPos = getPosition();
		bulletPos.y -= 32; // Adjust this y value based on your desired offset (negative = up)
		bulletPos.x -= 16; // Adjust this x value based on your desired offset (negative = left)

		Bullet* newBullet = new Bullet(bulletPos, false);  // Create bullet object
		bullets.push_back(newBullet);  // Add to bullets vector
		firetime = 0.7f;
	}

	// Prevent player from going off screen (left or right bounds)
	if (getPosition().x < 16) {
		setPosition(16, getPosition().y); // Left bound
	}
	if (getPosition().x > gameWidth - 16) {
		setPosition(gameWidth - 16, getPosition().y); // Right bound
	}
}

