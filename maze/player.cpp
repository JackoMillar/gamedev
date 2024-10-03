//player.cpp
#include "player.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::W,   // Player Up
	Keyboard::S,   // Player Down
	Keyboard::A,  // Player Left
	Keyboard::D // Player Right
};

void Player::Update(double dt) {

	// Move in four directions based on keys
	float directionx = 0.0f;
	float directiony = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		directiony--;
		
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		directiony++;
		
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		directionx--;
		
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		directionx++;
		
	}
	// Only move if there is input

		_position += Vector2f(directionx * _speed * dt, directiony * _speed * dt);

		// Move the shape to reflect the new position
		_shape->setPosition(_position);
	

	Entity::Update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}