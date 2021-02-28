#include "Bullet.h"

Bullet::Bullet(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
    shape.setTexture(*texture);

    this->shape.setPosition(pos_x, pos_y);
    direction.x = dir_x;
    direction.y = dir_y;
    movementSpeed = movement_speed;
}

const sf::FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}

const float& Bullet::getMovementSpeed() const
{
    return movementSpeed;
}

void Bullet::setMovementSpeed(const float speed)
{
    movementSpeed = speed;
}

void Bullet::update()
{
    shape.move(movementSpeed * direction);
}

void Bullet::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
