#pragma once

#include <SFML/Graphics.hpp>    
#include <SFML/System.hpp>

class Bullet
{
private:
    sf::Sprite shape;

    sf::Vector2f direction;
    float movementSpeed;

public:
    Bullet() {}
    Bullet(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float movementSpeed);
    virtual ~Bullet() {}

    //Accessor
    const sf::FloatRect getBounds() const;
    const float& getMovementSpeed() const;

    //Modifiers
    void setMovementSpeed(const float speed);

    void update();
    void render(sf::RenderTarget * target);
};