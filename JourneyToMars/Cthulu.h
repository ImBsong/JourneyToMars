#ifndef CTHULU_H
#define CTHULU_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"

class Cthulu : public Entity
{
private:
    bool goingLeft = true; // Currently only goes left and right
    float upDownTimer;
    int pauseAttack;
    int spawnTimer;
    int spawnThreshold;

public:
    void initVariables();
    void initTexture();
    void initSprite();

    void updateAttack();
    void update();
};

#endif // !CTHULU_H