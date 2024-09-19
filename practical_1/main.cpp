#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::W,   // Player1 UP
    Keyboard::S,   // Player1 Down
    Keyboard::Up,  // Player2 UP
    Keyboard::Down // Player2 Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;

Vector2f ballVelocity;
bool isPlayer1Serving = false;
const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;
const float velocityMultiplier = 1.1f;


CircleShape ball;
RectangleShape paddles[2];

void Load() {
    // Set size and origin of paddles
    for (auto& p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(5, 5); //Should be half the ball width and height
    // reset paddle position
    paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2f(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f));
    // reset Ball Position
    ball.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));

    ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };

}

void Reset(bool isPlayer1Serving) {

    paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2f(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f));
    // reset Ball Position
    ball.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));

    ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };


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

    ball.move(ballVelocity * dt);

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // handle paddle movement
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(Vector2f(0.f, direction * paddleSpeed * dt));

    direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[2])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        direction++;
    }
    paddles[1].move(Vector2f(0.f, direction * paddleSpeed * dt));

    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { //bottom wall
        // bottom wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2f(0.f, -10.f));
    }
    else if (by < 0) { //top wall
        // top wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2f(0.f, 10.f));
    }
    else if (bx > gameWidth) {
        // right wall
        Reset(true);
    }
    else if (bx < 0) {
        // left wall
        Reset(false);
    }
    else if (
        //ball is inline or behind paddle AND
        bx < paddleSize.x + paddleOffsetWall &&
        //ball is below top edge of paddle AND
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
    {
        // bounce off left paddle
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(Vector2f(10.f, 0.f));
    }
    else if (
        // ball is inline or behind paddle AND
        bx > gameWidth - paddleSize.x - paddleOffsetWall &&  // Fixed this line
        // ball is below top edge of paddle AND
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
        // ball is above bottom edge of paddle
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
    {
        // bounce off right paddle
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(Vector2f(-10.f, 0.f));
    }

    // Check paddle Collison
    const float cy = paddles[0].getPosition().y;

    const float vy = paddles[1].getPosition().y;
    if (cy > gameHeight - 50) { //bottom wall
        paddles[0].move(Vector2f(0.f, -10.f));
    }
    else if (cy < 50) { //top wall
        paddles[0].move(Vector2f(0.f, 10.f));
    }

    if (vy > gameHeight - 50) { //bottom wall
        paddles[1].move(Vector2f(0.f, -10.f));
    }
    else if (vy < 50) { //top wall
        paddles[1].move(Vector2f(0.f, 10.f));
    }

}

void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}