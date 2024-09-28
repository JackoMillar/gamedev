#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
    // Constructor
    Bullet(const sf::Vector2f& pos, const bool mode);

    // Destructor
    virtual ~Bullet();  // Use virtual destructor if you're using polymorphism

    // Update function
    void Update(const float& dt);

    static void Render(sf::RenderWindow& window);

    static void Fire(const sf::Vector2f& pos, const bool mode);

    static void Init();
private:
    bool _mode;

protected:
    static unsigned char bulletPointer;
    static Bullet bullets[256];
    //Called by the static Update()
    void _Update(const float& dt);
    //Never called by our code
    Bullet();
};