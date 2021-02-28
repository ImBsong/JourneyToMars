#include "Cthulu.h"

void Cthulu::initVariables()
{
    movementSpeed = 5.f;

    hpMax = 100;
    hp = hpMax;

    attackCooldownMax = 8.f;
    attackCooldown = attackCooldownMax;

    pauseAttack = 0;
}

void Cthulu::initTexture()
{
    //Load a texture from file

    if (!texture.loadFromFile("Textures/cthulu_boss.png"))
        std::cout << "Error: Cthulu Image did not load" << std::endl;
}

void Cthulu::initSprite()
{
    //Set the texture to the sprite
    sprite.setTexture(texture);

    //Resize 
    sprite.scale(.2f, .2f);
}

void Cthulu::updateAttack()
{
    if (attackCooldown < attackCooldownMax)
        attackCooldown += 2.f;
}

void Cthulu::update()
{

    if (getBounds().left < 0)
        goingLeft = false;
    if (getBounds().left + getBounds().width > 1920)
        goingLeft = true;

    if (goingLeft)
        move(-1.f, 0.f);
    else
        move(1.f, 0.f);

    // Quick and dirty code to have cthulu fire in intervals.  Not my proudest. Needs refactor
    if (pauseAttack < 100)
    {
        updateAttack();
        ++pauseAttack;
    }
    if (pauseAttack >= 100)
        ++pauseAttack;
    if (pauseAttack > 300)
        pauseAttack = 0;
}

