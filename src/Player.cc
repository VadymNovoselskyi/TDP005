#include "Player.h"

#include <iostream>

#include "TextureManager.h"

Player::Player(float maxHP,
               float currentHP,
               int movementSpeed,
               sf::Vector2f positon,
               sf::Vector2f direction,
               std::string name,
               int xp,
               int maxXP,
               int levels,
               float damageMultiplier)
    : Character("player", maxHP, currentHP, movementSpeed, positon, direction), name{name}, xp{xp},
      maxXP{maxXP}, levels{levels}, damageMultiplier{damageMultiplier},
      texture{TextureManager::instance()->getTexture("player.png")}
{
    auto player_size{texture->getSize()};

    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(player_size.x / 2, player_size.y);
    //create box for xp and hp
    sf::RectangleShape HPBox(sf::Vector2(150.f, 50.f));
    sf::RectangleShape CurrentHPBox(sf::Vector2(150.f, 50.f));
    
    sf::RectangleShape XPBox(sf::Vector2(150.f, 50.f));
    sf::RectangleShape CurrentXPBox(sf::Vector2(150.f, 50.f));
}

void Player::setXP(int gainedXP)
{
    xp += gainedXP;
    if (xp <= maxXP)
    {
        xp = -maxXP;
        maxXP += 100; // variabel för ökning + räkn med* - avrunda
                      // levelUp();
    }
}

void Player::move()
{
    direction.x = 0;
    direction.y = 0;
    //add rotation

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        direction.y = NORTH;
        rotation = UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x = EAST;
        rotation = LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y = SOUTH;
        rotation = DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        rotation = RIGHT;
        direction.x = WEST;
    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {

        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);

        //matematic explination: https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-2/trigonometri/radianer#!/
        //used to check calculation with degrees
        
        if(direction.y >= 0) //ner
        {
            //multiplying by (180/PI)to convert radian to degrees and subtract to flip rotation. 
            rotation = 180.f - std::asin(direction.x) * (180.f / M_PI);
        }
        else // up
        {
            rotation =  std::asin(direction.x) * (180.f / M_PI);
        }

    }

    sf::Sprite::setRotation(rotation);
    sf::Sprite::move(sf::Vector2f(direction.x * movementSpeed, direction.y * movementSpeed));
}
void Player::onCollision(std::string other)
{
    if (other == "enemy")
    {
    }
}

void Player::die()
{
    StateMachine::instance()->finishGame();
}

void Player::draw(sf::RenderWindow *window)
{
    window->draw(*this);
    drawInfo(10.0, 10.0, 150.0, 50.0);
}


void Player::drawInfo(float boxPosX, float boxPosY, float boxWidth, float boxheight)
{
    drawBox(boxPosX, boxPosY, boxWidth, boxheight, 128, 0 ,0 ); // hp box background
    drawBox(boxPosX, boxPosY, boxWidth * ( currentHP / maxHP), boxheight, 204, 0 ,0 ); // curent hp
    drawBox(boxPosX, boxPosY +60, boxWidth, boxheight, 76, 154 ,42 ); // xp background
    if (xp < 0)
    {
        drawBox(boxPosX, boxPosY +60, boxWidth * (xp / maxXP), boxheight, 118, 186 ,27 ); // current xp
    }
    else
    {
        drawBox(boxPosX, boxPosY +60, 0.1, boxheight, 118, 186 ,27 ); // current xp
    }
    

    // drawXP(boxPosX, boxPosY -60, boxWidth, boxheight);
}
void Player::drawBox(float boxPosX, float boxPosY, float boxWidth, float boxheight, int r, int g, int b)
{
    // Hp box background + outline
    sf::RectangleShape box(sf::Vector2(boxWidth, boxheight));
    box.setSize(sf::Vector2f(boxWidth, boxheight));
    box.setFillColor(sf::Color(r, g, b));
    box.setPosition(boxPosX, boxPosY);
    
}

void Player::levelUP(Choises choise)
{
    xp = 0; 
    switch (choise)
    {
    case HP: // hp
        maxHP += 50;
        break;
    case SPEED: // speed
        movementSpeed += 5;
        break;

    case DAMAGE: // damage
        damageMultiplier += 0.5;
    case WEAPON: // weapon

        break;
    }
}
