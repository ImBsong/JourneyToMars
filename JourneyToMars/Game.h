#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Cthulu.h"

class Game
{
private:
    //Window
    sf::RenderWindow * window;

    //Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> lasers;

    //GUI
    sf::Font font;
    sf::Text pointText;

    sf::Text gameOverText;
    sf::Text gameWonText;

    //World
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;

    //Systems
    unsigned int points;
    unsigned int gameTime;

    //Music
    sf::Music music;

    //SFX
    sf::SoundBuffer sfxBoostBufferBasicAttack;
    sf::Sound sfxBoostBasicAttack;
    //SFX - Enemy Hit
    sf::SoundBuffer sfxBoostBufferEnemyHit;
    sf::Sound sfxBoostBasicAttackEnemyHit;
    //SFX - Player Damage Taken
    sf::SoundBuffer sfxBoostBufferPlayerHit;
    sf::Sound sfxBoostBasicAttackPlayerHit;
    //SFX - Cthulu Attacks
    sf::SoundBuffer sfxBoostBufferCthuluAttack;
    sf::Sound sfxBoostBasicCthuluAttack;
    //SFX - Cthulu Enters!
    sf::SoundBuffer sfxBoostBufferCthuluEnters;
    sf::Sound sfxBoostCthuluEnters;
    //SFX - Cthulu Takes Damage!
    sf::SoundBuffer sfxBoostBufferCthuluTakesDamage;
    sf::Sound sfxBoostCthuluTakesDamage;

    //Player
    Entity * player;

    //Cthulu Boss
    Entity * cthulu;

    //Player Health Bar
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBack;

    //Cthulu Health Bar
    sf::RectangleShape CthuluHpBar;
    sf::RectangleShape CthuluHpBack;

    //Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;

    //Private functions
    void initWindow();
    void initTextures();
    void initGui();
    void initWorld();
    void initSystems();
    void initSounds();

    void initPlayer();
    void initEnemies();
    void initCthulu();

public:
    //Constructor and Destructor
    Game();
    virtual ~Game();

    //Functions
    void run();

    void updatePollEvents();
    void updateInput();
    void updateGui();
    void updateCollision();
    void updateBullets();
    void updateEnemies();
    void updateCombat();
    void update();
    void reset();

    void renderGui();
    void renderWorld();
    void render();
};
