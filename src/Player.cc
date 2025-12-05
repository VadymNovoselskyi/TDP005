#include "Player.h"
Player::Player(int maxHP,
               int currentHP,
               int movementSpeed,
               Point positon,
               Point direction,
               std::string name,
               int xp,
               int maxXP,
               int levels,
               double damageMultipplyer)
    : Character("player", maxHP, currentHP, movementSpeed, positon, direction), name{name}, xp{xp},
      maxXP{maxXP}, levels{levels}, damageMultipplyer{damageMultipplyer}
{
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        // figure.move(0, -SPEED);
        direction.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        // figure.move(-SPEED, 0);
        direction.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        // figure.move(0, SPEED);
        direction.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        // figure.move(SPEED, 0);
        direction.x = 1;
    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {
        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);
    }
    // figure.move(sf::Vector2f(direction.x * movementSpeed, direction.y * movementSpeed));
}
void Player::die()
{
    StateMachine::instance()->finishGame();
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