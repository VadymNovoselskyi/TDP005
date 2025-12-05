#include "Player.h"
Player::Player(float maxHP,
               float currentHP,
               int movementSpeed,
               Point positon,
               Point direction,
               std::string name,
               int xp,
               int maxXP,
               int levels,
               float damageMultipler,
               float boxWidth,
               float boxHeight)
    : Character(maxHP, currentHP, movementSpeed, positon, direction), 
    name{name}, xp{xp},maxXP{maxXP}, levels{levels}, damageMultipler{damageMultipler}, boxWidth{100},boxHeight{50}{}

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
        direction.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
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
void Player::drawInfo()
{
    drawHP();
    drawXP();
}
void Player::drawHP()
{
    // boxWidth =
    // Hp box background + outline
    sf::RectangleShape HpBox(sf::Vector2f(boxWidth, boxHeight));
    HpBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    HpBox.setFillColor(sf::Color(128, 0, 0));
    HpBox.setPosition(10.f, 10.f);
    // current hp
    sf::RectangleShape CurrentHp(sf::Vector2f(boxWidth, boxHeight));
    CurrentHp.setSize(sf::Vector2f(boxWidth, boxHeight));
    CurrentHp.setFillColor(sf::Color(204, 0, 0));
    CurrentHp.setPosition(10.f, 10.f);
}

void Player::levelUP(int uppgrade)
{
    switch (uppgrade)
    {
    case 1: // hp
        maxHP += uppgrade;
        break;

    case 2: // speed
        movementSpeed += uppgrade;
        break;

    case 3: // damage
        damageMultipler += uppgrade;
    case 4: // weapon

        break;
    }
}
