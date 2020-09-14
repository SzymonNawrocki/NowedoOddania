#include "bonus.h"

void bonus::initVariables()
{
    this->pointCount = rand() % 20 + 2;
    this->extradir = rand() % -10 + 2;
    this->type		= 0;
    this->speed		= static_cast<float>(this->pointCount/3);
    this->direct	= static_cast<float>(this->extradir/3);
    this->hpMax		= static_cast<int>(this->pointCount);
    this->hp		= this->hpMax;
    this->damage	= this->pointCount;
    this->points	= this->pointCount;
}

bonus::bonus(sf::Texture* texture,float pos_x, float pos_y)
{
    this->shapeb.setTexture(*texture);
    this->shapeb.scale(0.5f,0.6f);
    this->initVariables();


    this->shapeb.setPosition(pos_x, pos_y);
}

bonus::~bonus()
{

}


const sf::FloatRect bonus::getBounds() const
{
    return this->shapeb.getGlobalBounds();
}

const int & bonus::getPoints() const
{
    return this->points;
}

const int & bonus::getDamage() const
{
    return this->damage;
}


void bonus::update()
{
    this->shapeb.move(this->direct, this->speed);
}

void bonus::render(sf::RenderTarget * target)
{
    target->draw(this->shapeb);
}
