#include "Player.h"

#include <iostream>

#include "TextureManager.h"

Player::Player(double maxHP,
               double currentHP,
               int movementSpeed,
               sf::Vector2f positon,
               sf::Vector2f direction,
               std::string name,
               int levels,
               float damageMultiplier)
    : Character("player", maxHP, currentHP, movementSpeed, positon, direction), name{name}, levels{levels}, damageMultiplier{damageMultiplier},
      texture{TextureManager::instance()->getTexture("player.png")}
{
    auto player_size{texture->getSize()};

    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(player_size.x / 2, player_size.y);
    
}

void Player::move()
{
    direction.x = 0;
    direction.y = 0;
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
        direction.x = WEST;
        rotation = RIGHT;
    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {

        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);

        //matematic explination: https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-2/trigonometri/radianer#!/
        //used to check calculation with degrees
        
        if(direction.y >= 0) //down
        {
            //multiplying by (180/PI)to convert radian to degrees and subtract to flip rotation. 
            rotation = 180.f - std::asin(direction.x) * (180.f / M_PI);
        }
        else // up
        {
            rotation =  std::asin(direction.x) * (180.f / M_PI);
        }

    } // https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-1/trigonometri/enhetscirkeln#!/ - fixa rotaiton utifrån mus

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
    drawInfo(window);
}

void Player::drawInfo(sf::RenderWindow *window)
{
    // -fixa position utifrån kamera 
    // drawBox(window, HPBox, positon.x +60, positon.y -60, 150, 50, 128, 0 ,0 ); // hp box background
    // drawBox(window, CurrentHPBox, positon.x +60, positon.y -60, 150 * ( currentHP / maxHP), 50, 204, 0 ,0 ); // curent hp
    
    // drawBox(window, XPBox, positon.x +120, positon.y - 120 +60, 150, 50, 76, 154 ,42 ); // xp background
    // if (xp < 0)
    // {
    //     drawBox(window, CurrentXPBox, positon.x +120,  positon.y - 120, 150 * (xp / maxXP), 50, 118, 186 ,27 ); // current xp
    // }
    // else
    // {
    //     drawBox(window, CurrentXPBox, positon.x +120, positon.y - 120, 0.1, 50, 118, 186 ,27 ); // current xp
    // }

}
void Player::drawBox(sf::RenderWindow *window, sf::RectangleShape box, float boxPosX, float boxPosY, float boxWidth, float boxheight, int r, int g, int b)
{
    box.setSize(sf::Vector2f(boxWidth, boxheight));
    box.setFillColor(sf::Color(r, g, b));
    box.setPosition(boxPosX, boxPosY);
    window->draw(box);
}

// void Player::levelUP(Choises choise) // skapa levelup manager
// {
//     switch (choise)
//     {
//     case HP: // hp
//         maxHP += 50;
//         break;
//     case SPEED: // speed
//         movementSpeed += 5;
//         break;

//     case DAMAGE: // damage
//         damageMultiplier += 0.5;
//     case WEAPON: // weapon

//         break;
//     }
// }