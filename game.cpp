#include "game.h"

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Farm360", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textury/bullet.png");
    this->textures["ENEMY"] = new sf::Texture();
    this->textures["ENEMY"]->loadFromFile("Textury/ScareCrow.png");
    this->textures["BONUS"] = new sf::Texture();
    this->textures["BONUS"]->loadFromFile("Textury/owoc.png");
}

void Game::initGUI()
{

    this->font.loadFromFile("Fonts/PixellettersFull.ttf");
    this->pointText.setPosition(700.f, 25.f);
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(20);
    this->pointText.setFillColor(sf::Color::White);
    this->pointText.setString("xxx");
    this->pointTextmovment.setPosition(25.f, 45.f);
    this->pointTextmovment.setFont(this->font);
    this->pointTextmovment.setCharacterSize(20);
    this->pointTextmovment.setFillColor(sf::Color::White);
    this->pointTextmovment.setString("Move-WSAD\n Shooting-UpDownLeftRight");
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(30);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setPosition(
        this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
    this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    this->playerHpBar.setFillColor(sf::Color::Red);
    this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

    this->playerHpBarBack = this->playerHpBar;
    this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
    this->worldBackgroundTex.loadFromFile("Textury/grid_bg.png");

    this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
    this->points = 0;
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initEnemies()
{
    this->spawnTimerMax = 30.f;
    this->spawnTimer = this->spawnTimerMax;
}

void Game::initbonus()
{
    this->spawnbTimerMax = 50.f;
    this->spawnbTimer = this->spawnbTimerMax;
}
Game::Game()
{
    this->initWindow();
    this->initTextures();
    this->initGUI();
    this->initWorld();
    this->initSystems();
    this->initbonus();
    this->initPlayer();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
    delete this->player;


    for (auto &i : this->textures)
    {
        delete i.second;
    }


    for (auto *i : this->bullets)
    {
        delete i;
    }


    for (auto *i : this->enemies)
    {
        delete i;
    }

    for (auto *i : this->bonuses)
    {
        delete i;
    }
}


void Game::run()
{
    while (this->window->isOpen())
    {
        this->updatePollEvents();

        if(this->player->getHp() > 0)
            this->update();

        this->render();
    }
}

void Game::updatePollEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
            this->window->close();
    }
}

void Game::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        this->bonuses.push_back(new bonus(this->textures["BONUS"],rand() % this->window->getSize().x-10.f, -100.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet(this->textures["BULLET"],this->player->getPos().x + this->player->getBounds().width/2.f,this->player->getPos().y,0.f,-1.f,5.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet( this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width/2.f, this->player->getPos().y,0.f, 1.f,5.f ) );
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet(  this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width/2.f, this->player->getPos().y,-1.f, 0.f,5.f ) );
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->player->canAttack())
    {
        this->bullets.push_back(
            new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width/2.f, this->player->getPos().y, 1.f, 0.f, 5.f ) );
    }
}

void Game::updateGUI()
{
    std::stringstream ss;

    ss << "Points: " << this->points;

    this->pointText.setString(ss.str());


    float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
    this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{

    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }

    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }


    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }

    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
}

void Game::updateBullets()
{
    unsigned counter = 0;
    for (auto *bullet : this->bullets)
    {
        bullet->update();


        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {

            delete this->bullets.at(counter);
            this->bullets.erase(this->bullets.begin() + counter);
        }

        ++counter;
    }
}

void Game::updateEnemies()
{

    this->spawnTimer += 0.5f;
    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(this->textures["ENEMY"],rand() % this->window->getSize().x-20.f, -100.f));
        this->spawnTimer = 0.f;
    }


    unsigned counter = 0;
    for (auto *enemy : this->enemies)
    {
        enemy->update();


        if (enemy->getBounds().top > this->window->getSize().y)
        {

            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }

        else if(enemy->getBounds().intersects(this->player->getBounds()))
        {
            this->player->loseHp(this->enemies.at(counter)->getDamage());
            delete this->enemies.at(counter);
            this->enemies.erase(this->enemies.begin() + counter);
        }

        ++counter;
    }
}
void Game::updatebonus()
{

    this->spawnbTimer += 0.1f;
    if (this->spawnbTimer >= this->spawnbTimerMax)
    {
        this->bonuses.push_back(new bonus(this->textures["BONUS"],rand() % this->window->getSize().x-10.f, -90.f));
        this->spawnbTimer = 0.f;
    }


    unsigned counter = 0;
    for (auto *bon : this->bonuses)
    {
        bon->update();

         if(bon->getBounds().intersects(this->player->getBounds()))
        {
            this->player->healHp(this->bonuses.at(counter)->getDamage());
            delete this->bonuses.at(counter);
            this->bonuses.erase(this->bonuses.begin() + counter);
        }

        ++counter;
    }
}
void Game::updateCombat()
{
    for (int i = 0; i < this->enemies.size(); ++i)
    {
        bool enemy_deleted = false;
        for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
        {
            if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {
                this->points += this->enemies[i]->getPoints();

                delete this->enemies[i];
                this->enemies.erase(this->enemies.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                enemy_deleted = true;
            }
        }
    }

    for (int i = 0; i < this->bonuses.size(); ++i)
    {
        bool bonus_deleted = false;
        for (size_t k = 0; k < this->bullets.size() && bonus_deleted == false; k++)
        {
            if (this->bonuses[i]->getBounds().intersects(this->bullets[k]->getBounds()))
            {
                this->points += this->bonuses[i]->getPoints();

                delete this->bonuses[i];
                this->bonuses.erase(this->bonuses.begin() + i);

                delete this->bullets[k];
                this->bullets.erase(this->bullets.begin() + k);

                bonus_deleted = true;
            }
        }
    }
}

void Game::update()
{
    this->updateInput();

    this->player->update();

    this->updateCollision();

    this->updateBullets();

    this->updateEnemies();

    this->updatebonus();

    this->updateCombat();

    this->updateGUI();

    this->updateWorld();
}

void Game::renderGUI()
{
    this->window->draw(this->pointText);
    this->window->draw(this->pointTextmovment);
    this->window->draw(this->playerHpBarBack);
    this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
    this->window->draw(this->worldBackground);
}

void Game::render()
{
    this->window->clear();


    this->renderWorld();


    this->player->render(*this->window);

    for (auto *bullet : this->bullets)
    {
        bullet->render(this->window);
    }

    for (auto *enemy : this->enemies)
    {
        enemy->render(this->window);
    }
    for (auto *bonus : this->bonuses)
    {
        bonus->render(this->window);
    }

    this->renderGUI();


    if (this->player->getHp() <= 0)
        this->window->draw(this->gameOverText);

    this->window->display();
}
