#include "Player.h"
#include <iostream>

void Player::initVariables()
{
    movementSpeed = 5.f;

    hpMax = 100;
    hp = hpMax;

    attackCooldownMax = 10.f;
    attackCooldown = attackCooldownMax;
}

void Player::initTexture()
{
    //Load a texture from file

    if (!texture.loadFromFile("Textures/ship.png"))
        std::cout << "Error: Player Image did not load" << std::endl;
}

void Player::initSprite()
{
    //Set the texture to the sprite
    sprite.setTexture(texture);

    //Resize 
    sprite.scale(.1f, .1f);
}

void Player::updateAttack()
{
    if (attackCooldown < attackCooldownMax)
        attackCooldown += .5f;
}

void Player::update()
{
    updateAttack();
}