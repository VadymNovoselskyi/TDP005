#include "Player.h"

#include <iostream>

Player::Player(int maxHP,
               int currentHP,
               int movementSpeed,
               sf::Vector2f positon,
               sf::Vector2f direction,
               std::string name,
               int xp,
               int maxXP,
               int levels,
               double damageMultipplyer)
    : Character("player", maxHP, currentHP, movementSpeed, positon, direction), name{name}, xp{xp},
      maxXP{maxXP}, levels{levels}, damageMultipplyer{damageMultipplyer}, texture{}
{
    texture.loadFromFile("static/fighter.png");
    auto player_size{texture.getSize()};

    sf::Sprite::setTexture(texture);
    sf::Sprite::setOrigin(player_size.x / 2, player_size.y);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        // std::cout << "W pressed" << std::endl;
        // figure.move(0, -SPEED);
        direction.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        // std::cout << "A pressed" << std::endl;
        // figure.move(-SPEED, 0);
        direction.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // std::cout << "S pressed" << std::endl;
        // figure.move(0, SPEED);
        direction.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        // std::cout << "D pressed" << std::endl;
        // figure.move(SPEED, 0);
        direction.x = 1;
    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {
        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);
    }
    sf::Sprite::move(sf::Vector2f(direction.x * movementSpeed, direction.y * movementSpeed));
}
void Player::die()
{
    StateMachine::instance()->finishGame();
}

void Player::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    // Draw HP and XP too plz
}

void Player::onCollision(std::string other)
{
    if (other == "enemy")
    {

    }
}

// void Player::drawHP(bool boxPosX, bool boxPosY, float boxWidth, float boxheight)
// {
//    //Hp box background + outline
//     sf::RectangleShape HpBox(sf::Vector2(boxWidth, boxheight));
//     HpBox.setSize(sf::Vector2f(boxWidth, boxheight));
//     HpBox.setFillColor(sf::Color(128,0,0));
//     HpBox.setPosition(boxPosX, boxPosY);
//     //current hp
//     sf::RectangleShape CurrentHp(sf::Vector2(boxWidth, boxheight));
//     CurrentHp.setSize(sf::Vector2f(boxWidth, boxheight));
//     CurrentHp.setFillColor(sf::Color(204,0,0));
//     CurrentHp.setPosition(boxPosX, boxPosY);
// }

// void Player::levelUp(std::string choise, auto uppgrade)
// {
//   switch (choise)
//   {
//     case "Health":
//       maxHP += uppgrade;
//       break;

//       case "Speed":
//       movementSpeed += uppgrade;
//       break;

//       case "Damage":
//       damageMultipplyer += uppgrade;
//       case "Weapon":

//       break;
//   }

// }