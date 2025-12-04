#include "Player.h"
Player::Player(int maxHp,
               int currentHP,
               int movementSpeed,
               Point positon,
               Point direction,
               std::string name,
               int xp,
               int maxXp,
               int levels,
               double damageMultipplyer)
    : Character(maxHP, currentHP, movementSpeed, positon, direction), name{name}, xp{xp},
      levels{levels}, damageMultipplyer{damageMultipplyer}
{
}

void Player::setXP(int gainedXP)
{
  xp += gainedXP;
  if (xp <= maxXp)
  {
    xp =- maxXp;
    maxXp += 100; // variabel för ökning + räkn med* - avrunda
      //levelUp();
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

void Player::levelUp(std::string choise, auto uppgrade)
{
  switch (choise)
  {
    case "Health":
      maxHP += uppgrade;
      break;

      case "Speed":
      movementSpeed += uppgrade;
      break;

      case "Damage":
      damageMultipplyer += uppgrade;
      case "Weapon":
        
      break;
  }
  
}
void Player::move()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
      // figure -> player
       // figure.move(0, -movementSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
      //  figure.move(-movementSpeed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
      //  figure.move(0, movementSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
       // figure.move(movementSpeed, 0);
       return;
    }

}
