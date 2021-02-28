#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>

// This is really the asteroids.  Enemy is not quite accurate

class Enemy
{
private:
    unsigned pointCount;
    sf::CircleShape shape;
    int type;
    int hp;
    int hpMax;
    int damage;
    int points;
    float speed;

    void initVariables();
    void initShape();

public:
    Enemy(float posX, float posY);
    virtual ~Enemy() {}

    //Accessors
    sf::FloatRect getBounds() const;
    int getPoint() const;
    int getDamage() const;

    //Functions
    void update();
    void render(sf::RenderTarget * target);
};

#endif // !ENEMY_H