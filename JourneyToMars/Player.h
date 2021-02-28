#pragma once

#include <SFML/Graphics.hpp>    
#include <SFML/System.hpp>

#include "Entity.h"

class Player : public Entity
{
public:
    void initVariables();
    void initTexture();
    void initSprite();

    void updateAttack();
    void update();
};