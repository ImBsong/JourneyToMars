#pragma once

#include <SFML/Graphics.hpp>    
#include <SFML/System.hpp>

/*
    Abstract Base Class
*/
class Entity
{
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;

    float attackCooldown;
    float attackCooldownMax;

    int hpMax;
    int hp;
public:
    // Empty Constructor and Destructor.  Pointer is deleted in game file
    Entity() {}
    virtual ~Entity() {}

    // Virtual Initializers
    virtual void initVariables() = 0;
    virtual void initTexture() = 0;
    virtual void initSprite() = 0;

    // Accessors
    const sf::Vector2f& getPos() const;
    sf::FloatRect getBounds() const;
    const int& getHp() const;
    const int& getHpMax() const;

    // Modifiers
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);

    void move(const float dirX, const float dirY);
    bool canAttack();

    // Update.  This is virtual as diff entities behave differently
    virtual void updateAttack() = 0;
    virtual void update() = 0;

    // Render.  
    void render(sf::RenderTarget& target);
};

