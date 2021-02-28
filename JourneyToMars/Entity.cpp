#include "Entity.h"

const sf::Vector2f & Entity::getPos() const
{
    return sprite.getPosition();
}

sf::FloatRect Entity::getBounds() const
{
    return sprite.getGlobalBounds();
}

const int & Entity::getHp() const
{
    return hp;
}

const int & Entity::getHpMax() const
{
    return hpMax;
}

void Entity::setPosition(const sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Entity::setPosition(const float x, const float y)
{
    sprite.setPosition(x, y);
}

void Entity::setHp(const int hp)
{
    this->hp = hp;
}

void Entity::loseHp(const int value)
{
    this->hp -= value;
    if (this->hp < 0)
        this->hp = 0;
}

void Entity::move(const float dirX, const float dirY)
{
    sprite.move(movementSpeed* dirX, movementSpeed * dirY);
}

bool Entity::canAttack()
{
    if (attackCooldown >= attackCooldownMax)
    {
        attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Entity::render(sf::RenderTarget & target)
{
    target.draw(sprite);
}

