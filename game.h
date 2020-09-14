#pragma once

#include<map>
#include<string>
#include<sstream>
#include"player.h"
#include"bullet.h"
#include"enemy.h"
#include "bonus.h"

class Game
{
private:

    sf::RenderWindow* window;

    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

    sf::Font font;
    sf::Text pointText;
    sf::Text pointTextmovment;

    sf::Text gameOverText;

    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;


    unsigned points;
    Player* player;

    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;

    float spawnTimer;
    float spawnTimerMax;
    std::vector<Enemy*> enemies;
    float spawnbTimer;
    float spawnbTimerMax;
    std::vector<bonus*> bonuses;

    void initWindow();
    void initTextures();
    void initGUI();
    void initWorld();
    void initSystems();

    void initPlayer();
    void initEnemies();
    void initbonus();

public:
    Game();
    virtual ~Game();


    void run();

    void updatePollEvents();
    void updateInput();
    void updateGUI();
    void updateWorld();
    void updateCollision();
    void updateBullets();
    void updateEnemies();
    void updatebonus();
    void updateCombat();
    void update();

    void renderGUI();
    void renderWorld();
    void render();
};

