#include "Enemy.h"

void Enemy::initVariables()
{
    pointCount = rand() % 8 + 3;
    type = 0;
    speed = static_cast<float>(pointCount / 3);
    hpMax = static_cast<int>(pointCount);
    hp = hpMax;
    damage = pointCount + 3;
    points = pointCount;
}

void Enemy::initShape()
{
    shape.setRadius(static_cast<float>(pointCount * 4));
    shape.setPointCount(pointCount);
    shape.setFillColor(sf::Color::Color(139, 69, 19, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
    initVariables();
    initShape();

    shape.setPosition(pos_x, pos_y);
}

//Accessors
sf::FloatRect Enemy::getBounds() const
{
    return shape.getGlobalBounds();
}

int Enemy::getPoint() const
{
    return points;
}

int Enemy::getDamage() const
{
    return damage;
}

//Functions
void Enemy::update()
{
    shape.move(0.f, speed);
}

void Enemy::render(sf::RenderTarget * target)
{
    target->draw(shape);
}