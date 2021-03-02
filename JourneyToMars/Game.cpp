#include "Game.h" 

void Game::initWindow()
{
    sf::VideoMode videoMode = sf::VideoMode(1920, 1080);
    window = new sf::RenderWindow(videoMode, "Game 3", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
    textures["BULLET"] = new sf::Texture();
    if (!textures["BULLET"]->loadFromFile("Textures/bullet.png"))
        std::cout << "ERROR: BULLET DID NOT LOAD";

    textures["LASERBEAM"] = new sf::Texture();
    if (!textures["LASERBEAM"]->loadFromFile("Textures/laser.png"))
        std::cout << "ERROR: LASERBEAM DID NOT LOAD";
}

void Game::initGui()
{
    //Load font
    if (!font.loadFromFile("Fonts/alpha_echo.ttf"))
        std::cout << "ERROR: Font did not load!" << "\n";

    //Load Text
    pointText.setFont(font);
    pointText.setCharacterSize(24);
    pointText.setFillColor(sf::Color::White);
    pointText.setPosition(25.f, 40.f);

    //Game Over Text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over! Press R to Reset");
    gameOverText.setPosition(
        (window->getSize().x / 2.f) - gameOverText.getGlobalBounds().width / 2.f,
        window->getSize().y / 2.f - gameOverText.getGlobalBounds().height / 2.f);

    //Game Won Text
    gameWonText.setFont(font);
    gameWonText.setCharacterSize(100);
    gameWonText.setFillColor(sf::Color::Green);
    gameWonText.setString("You Win! Press R to Reset");
    gameWonText.setPosition(
        (window->getSize().x / 2.f) - gameWonText.getGlobalBounds().width / 2.f,
        window->getSize().y / 2.f - gameWonText.getGlobalBounds().height / 2.f);

    //Init Player GUI (Health Bar)
    playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    playerHpBar.setFillColor(sf::Color::Green);
    playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

    playerHpBack = playerHpBar;
    playerHpBack.setFillColor(sf::Color(25, 25, 25, 200));

    //Init Cthulu GUI (Health Bar)
    CthuluHpBar.setSize(sf::Vector2f(300.f, 25.f));
    CthuluHpBar.setFillColor(sf::Color::Red);
    CthuluHpBar.setPosition(sf::Vector2f(window->getSize().x - 320.f, 20.f));

    CthuluHpBack = CthuluHpBar;
    CthuluHpBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
    if (!worldBackgroundTex.loadFromFile("Textures/space_background.jpg"))
        std::cout << "ERROR: Background did not load!" << "\n";

    worldBackground.setTexture(worldBackgroundTex);
    worldBackground.setScale(1.2f, 1.15f);
}

void Game::initSystems()
{
    points = 0;
    gameTime = 0;
}

void Game::initSounds()
{
    // Music
    if (!this->music.openFromFile("Sounds/Resilience.ogg"))
        std::cout << "ERROR: Music did not load!\n";

    music.setVolume(7);
    music.play();

    // SFX
    // Missile Sound
    if (!sfxBoostBufferBasicAttack.loadFromFile("Sounds/SoundFX/laserSmall_000.ogg"))
        std::cout << "ERROR: Missile FX Did not load!\n";
    sfxBoostBasicAttack.setBuffer(sfxBoostBufferBasicAttack);

    // Enemy Hit
    if (!sfxBoostBufferEnemyHit.loadFromFile("Sounds/SoundFX/lowFrequency_explosion_000.ogg"))
        std::cout << "ERROR: Enemy Hit FX Did not load!\n";
    sfxBoostBasicAttackEnemyHit.setBuffer(sfxBoostBufferEnemyHit);

    // Player Hit
    if (!sfxBoostBufferPlayerHit.loadFromFile("Sounds/SoundFX/close_004.ogg"))
        std::cout << "ERROR: Player Hit FX Did not load!\n";
    sfxBoostBasicAttackPlayerHit.setBuffer(sfxBoostBufferPlayerHit);

    // Cthulu Attacks
    if (!sfxBoostBufferCthuluAttack.loadFromFile("Sounds/SoundFX/explosionCrunch_000.ogg"))
        std::cout << "ERROR: Cthulu Attack FX Did not load!\n";
    sfxBoostBasicCthuluAttack.setBuffer(sfxBoostBufferCthuluAttack);

    // Cthulu Enters
    if (!sfxBoostBufferCthuluEnters.loadFromFile("Sounds/SoundFX/laugh-evil-1.ogg"))
        std::cout << "ERROR: Cthulu Enters FX Did not load!\n";
    sfxBoostCthuluEnters.setBuffer(sfxBoostBufferCthuluEnters);

    // Cthulu Takes Damage
    if (!sfxBoostBufferCthuluTakesDamage.loadFromFile("Sounds/SoundFX/explosionCrunch_000.ogg"))
        std::cout << "ERROR: Cthulu Enters FX Did not load!\n";
    sfxBoostCthuluTakesDamage.setBuffer(sfxBoostBufferCthuluTakesDamage);
}

void Game::initPlayer()
{
    this->player = new Player();
    player->initVariables();
    player->initTexture();
    player->initSprite();

    //SetPosition 
    player->setPosition((window->getSize().x - player->getBounds().width) / 2, window->getSize().y - player->getBounds().height); // Set it center bottom
}

void Game::initEnemies()
{
    spawnTimerMax = 20.f;
    spawnTimer = spawnTimerMax;
}

void Game::initCthulu()
{
    this->cthulu = new Cthulu();
    cthulu->initVariables();
    cthulu->initTexture();
    cthulu->initSprite();

    //SetPosition 
    cthulu->setPosition(window->getSize().x + 1000.f, cthulu->getBounds().height / 2); // Hides to the right, then comes in with a laughter!
    sfxBoostCthuluEnters.play();
}

//Constructor and Destructor
Game::Game()
{
    initWindow();
    initTextures();
    initGui();
    initSystems();
    initWorld();
    initSounds();
    initPlayer();
    initEnemies();
    initCthulu();
}

Game::~Game()
{
    delete this->window;
    delete this->player;
    delete this->cthulu;

    //Delete textures
    for (auto i : this->textures)
    {
        delete i.second;
    }

    //Delete bullets
    for (auto *i : this->bullets)
    {
        delete i;
    }

    for (auto *i : this->enemies)
    {
        delete i;
    }
}

void Game::run()
{
    while (window->isOpen())
    {
        updatePollEvents();

        if (player->getHp() > 0 && cthulu->getHp() > 0)
        {
            update();
        }
        render();
    }
}

void Game::updatePollEvents()
{
    sf::Event sfmlEvent;

    while (window->pollEvent(sfmlEvent))
    {
        switch (sfmlEvent.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (sfmlEvent.key.code == sf::Keyboard::Escape)
                window->close();
            if (sfmlEvent.key.code == sf::Keyboard::R)
                reset();
            break;
        }
    }
}

void Game::updateInput()
{
    //Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player->move(-1.f, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player->move(0.f, -1.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player->move(0.f, 1.f);

    //If bullet button is pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->canAttack())
    {
        sfxBoostBasicAttack.play();

        bullets.push_back(
            new Bullet(
                textures["BULLET"],
                player->getPos().x + player->getBounds().width / 2.f,
                player->getPos().y,
                0.f,
                -1.f,
                5.f));
    }
}

void Game::updateGui()
{
    //Points
    std::stringstream ss;
    ss << "Points: " << points;
    pointText.setString(ss.str());

    //Update Player Health Bar
    float hpPercent = static_cast<float>(player->getHp()) / player->getHpMax();
    playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, playerHpBar.getSize().y));

    //Update Cthulu Health Bar
    float CthuluHpPercent = static_cast<float>(cthulu->getHp()) / cthulu->getHpMax();
    CthuluHpBar.setSize(sf::Vector2f(300.f * CthuluHpPercent, CthuluHpBar.getSize().y));

}

void Game::updateCollision()
{
    //Left and Right world collision
    if (player->getBounds().left < 0.f)
    {
        player->setPosition(0.f, player->getBounds().top);
    }
    else if (player->getBounds().left + player->getBounds().width > window->getSize().x)
    {
        player->setPosition(window->getSize().x - player->getBounds().width, player->getBounds().top);
    }

    //Top and Bottom world collision
    if (player->getBounds().top < 0.f)
    {
        player->setPosition(player->getBounds().left, 0.f);
    }
    else if (player->getBounds().top + player->getBounds().height > window->getSize().y)
    {
        player->setPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
    }

}

void Game::updateBullets()
{
    // Ship Bullet
    unsigned bulletCounter = 0;
    for (auto *bullet : bullets)
    {
        bullet->update();

        //Bullet culling (top of screen)
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            //Delete bullet
            delete bullets.at(bulletCounter);
            bullets.erase(bullets.begin() + bulletCounter);
            --bulletCounter;
        }
        ++bulletCounter;
    }

    // CTHULU ATTACK!
    if (cthulu->canAttack())
    {
        //Disable for now because need to make it wait
        //sfxBoostBasicCthuluAttack.play();

        lasers.push_back(
            new Bullet(
                textures["LASERBEAM"],
                cthulu->getPos().x + cthulu->getBounds().width / 2.f,
                cthulu->getPos().y + cthulu->getBounds().height,
                0.f,
                1.f,
                5.f));
    }
}

// Update enemies 
void Game::updateEnemies()
{
    //spawns enemies continuously
    spawnTimer += 1.f;
    if (spawnTimer >= spawnTimerMax)
    {
        enemies.push_back(new Enemy((rand() % (window->getSize().x - 200)) + 100.f, -100.f)); // makes the enemy spawn within (100, 1820)
        spawnTimer = 0.f;
    }

    //Update
    unsigned counter = 0;
    for (auto *enemy : enemies)
    {
        enemy->update();

        //Enemy Culling if they go bottom of screen
        if (enemy->getBounds().top > window->getSize().y)
        {
            //Delete Enemy
            delete enemies.at(counter);
            enemies.erase(enemies.begin() + counter);
        }

        //Enemy Player Collision
        else if (enemy->getBounds().intersects(player->getBounds()))
        {
            player->loseHp(enemies.at(counter)->getDamage());
            sfxBoostBasicAttackPlayerHit.play();
            delete enemies.at(counter);
            enemies.erase(enemies.begin() + counter);
        }
        ++counter;
    }

    unsigned laserCounter = 0;
    for (auto *laser : lasers) {
        laser->update();

        //Laser Culling (bot of screen)
        if (laser->getBounds().top > window->getSize().y)
        {
            delete lasers.at(laserCounter);
            lasers.erase(lasers.begin() + laserCounter);
            --laserCounter;
        }

        else if (laser->getBounds().intersects(player->getBounds()))
        {
            player->loseHp(20);
            sfxBoostBasicAttackPlayerHit.play();
            delete lasers.at(laserCounter);
            lasers.erase(lasers.begin() + laserCounter);
        }
        ++laserCounter;
    }
}

void Game::updateCombat()
{
    //Checks each enemy to see if they are hit.  Remove bullet and enemy if hit
    //Big O of ab
    for (int i = 0; i < this->enemies.size(); ++i)
    {
        bool enemy_deleted = false;
        for (size_t j = 0; j < bullets.size() && !enemy_deleted; j++)
        {
            if (enemies[i]->getBounds().intersects(bullets[j]->getBounds()))
            {
                points += enemies[i]->getPoint();
                sfxBoostBasicAttackEnemyHit.play();

                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                enemy_deleted = true;

                delete bullets[j];
                bullets.erase(bullets.begin() + j);
            }
        }
    }

    bool cthulu_deleted = false;
    for (int i = 0; i < bullets.size() && !cthulu_deleted; i++)
    {
        if (cthulu->getBounds().intersects(bullets[i]->getBounds()))
        {
            points += 10;
            sfxBoostCthuluTakesDamage.play();
            cthulu->loseHp(3);

            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Game::update()
{
    updateInput();
    player->update();
    cthulu->update();
    updateCollision();
    updateBullets();
    updateEnemies();
    updateCombat();
    updateGui();
}

void Game::reset()
{
    // First, delet all the old stuff
    delete this->player;
    delete this->cthulu;
    //for (auto i : this->textures)
    //{
    //    delete i.second;
    //}

    //Delete bullets
    for (auto *i : this->bullets)
    {
        delete i;
    }
    bullets.clear();

    for (auto *i : this->enemies)
    {
        delete i;
    }
    enemies.clear();

    for (auto *i : this->lasers)
    {
        delete i;
    }
    lasers.clear();


    // Re initialize
    initTextures();
    initGui();
    initSystems();
    initWorld();
    initPlayer();
    initEnemies();
    initCthulu();


}

void Game::renderGui()
{
    window->draw(pointText);
    window->draw(playerHpBack);
    window->draw(playerHpBar);
    window->draw(CthuluHpBack);
    window->draw(CthuluHpBar);
}

void Game::renderWorld()
{
    window->draw(worldBackground);
}

void Game::render()
{

    window->clear();
    renderWorld();
    player->render(*window);
    cthulu->render(*window);

    for (auto *bullet : bullets)
    {
        bullet->render(window);
    }
    for (auto *laser : lasers)
    {
        laser->render(window);
    }
    for (auto * enemy : enemies)
    {
        enemy->render(window);
    }

    renderGui();

    //Game over screens
    if (player->getHp() <= 0)
        window->draw(gameOverText);

    if (cthulu->getHp() <= 0)
        window->draw(gameWonText);

    window->display();
}
