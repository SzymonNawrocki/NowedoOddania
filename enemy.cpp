#include "enemy.h"

void Enemy::initVariables()
{
    this->pointCount = rand() % 10 + 2;
    this->type		= 0;
    this->speed		= static_cast<float>(this->pointCount/3);
    this->hpMax		= static_cast<int>(this->pointCount);
    this->hp		= this->hpMax;
    this->damage	= this->pointCount;
    this->ptk	= this->pointCount;
}


Enemy::Enemy(sf::Texture* texture,float pos_x, float pos_y)
{
    this->shape.setTexture(*texture);
    this->shape.scale(0.4f,0.4f);
    this->initVariables();


    this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}


const sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const int & Enemy::getPoints() const
{
    return this->ptk;
}

const int & Enemy::getDamage() const
{
    return this->damage;
}


void Enemy::update()
{
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
