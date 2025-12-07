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
    //skapa boxa för xp och hp
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
        direction.y = -1;
        rotation = 0.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x = -1;
        rotation = -90.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y = 1;
        rotation = 180.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        rotation = 90.f;
        direction.x = 1;
    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {

        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);
        //divide angle by 2 for rotation
        //rotation = rotation / 2;
        // rotation = 90.f * direction.x; // rotation up 
        // if (direction.y > 0) // rotation ned
        // {
        //     rotation = 180.f * direction.y;
        // }
        //matematisk förklaring: https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-2/trigonometri/trigonometriska-funktioner?#!/
        if(direction.y >= 0) //ner
        {
            rotation = 180.f - std::asin(direction.x) * (180.f / M_PI);
        }
        else // upnej itne med programering bara matte

        {
            rotation =  std::asin(direction.x) * (180.f / M_PI);
        }

    }

    sf::Sprite::setRotation(rotation);
    sf::Sprite::move(sf::Vector2f(direction.x * movementSpeed, direction.y * movementSpeed));
}
void Player::die()
{
    StateMachine::instance()->finishGame();
}

void Player::draw(sf::RenderWindow *window)
{
    window->draw(*this);
    // Draw HP and XP too plz
    drawInfo(10.0, 10.0, 150.0, 50.0);
}

void Player::onCollision(std::string other)
{
    if (other == "enemy")
    {
    }
}
void Player::drawInfo(float boxPosX, float boxPosY, float boxWidth, float boxheight)
{
    drawBox(boxPosX, boxPosY, boxWidth, boxheight, 128, 0 ,0 ); // hp box background
    drawBox(boxPosX, boxPosY, boxWidth, boxheight, 204, 0 ,0 ); // curent hp
    drawBox(boxPosX, boxPosY +60, boxWidth, boxheight, 76, 154 ,42 ); // xp background
    drawBox(boxPosX, boxPosY +60, boxWidth, boxheight, 118, 186 ,27 ); // current xp

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
