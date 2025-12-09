#include "Player.h"

#include <iostream>

#include "StateMachine.h"
#include "TextureManager.h"
#include "Window.h"

Player::Player(double maxHP,
               double currentHP,
               int movementSpeed,
               sf::Vector2f const &position,
               sf::Vector2f const &direction,
               std::string const &name,
               int levels,
               float damageMultiplier)
    : Character("player", maxHP, currentHP, movementSpeed, position, direction), name{name},
      levels{levels}, damageMultiplier{damageMultiplier},
      texture{TextureManager::instance()->getTexture("player.png")}
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

void Player::move()
{
    direction.x = 0;
    direction.y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        direction.y = NORTH;
        // rotation = UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x = EAST;
        // rotation = LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y = SOUTH;
        // rotation = DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        direction.x = WEST;
        // rotation = RIGHT;
    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {
        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);

        // matematic explination:
        // https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-2/trigonometri/radianer#!/
        // used to check calculation with degrees

        // if (direction.y >= 0) // down
        // {
        //     // multiplying by (180/PI)to convert radian to degrees and subtract to flip rotation.
        //     rotation = 180.f - std::asin(direction.x) * (180.f / M_PI);
        // }
        // else // up
        // {
        //     rotation = std::asin(direction.x) * (180.f / M_PI);
        // }

    } // 
      // - fixa rotaiton utifrån mus
    //     rotation = acos((sf::Mouse::getPosition().x - position.x) /
    //                       sqrt(pow(sf::Mouse::getPosition().x - position.x, 2) +
    //                            pow(sf::Mouse::getPosition().y - position.y, 2)))
    //                      * 180.f / 3.14159265f;

    // if (sf::Mouse::getPosition().y - position.y < 0)
    //     rotation = 360.f - rotation;

    sf::Sprite::move(sf::Vector2f(direction.x * movementSpeed, direction.y * movementSpeed));
}
void Player::uppdateRotation(sf::RenderWindow *window)
{
    //kollade upp om det fans någon atan funktion och hittad: https://cppreference.com/w/c/numeric/math/atan2.html
    //kollade upp hur jag skulle räkna enhetscirklen: https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-1/trigonometri/enhetscirkeln#!/
    double rotationRadians =
        std::atan2((sf::Mouse::getPosition(*window).y - (Window::WINDOW_HEIGHT / 2)),
                  (sf::Mouse::getPosition(*window).x - (Window::WINDOW_WIDTH / 2)));
    rotation = rotationRadians * (180 / M_PI) + 90; // transform radians to rtoation

    sf::Sprite::setRotation(rotation);
}

void Player::onCollision(std::string const &other)
{
    if (other == "enemy")
    {
    }
}

void Player::die()
{
    StateMachine::instance()->finishGame();
}

void Player::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    drawInfo(window);
}

void Player::drawInfo(sf::RenderWindow *window) const
{
    // -fixa position utifrån kamera
    // drawBox(window, HPBox, positon.x +60, positon.y -60, 150, 50, 128, 0 ,0 ); // hp box
    // background drawBox(window, CurrentHPBox, positon.x +60, positon.y -60, 150 * ( currentHP /
    // maxHP), 50, 204, 0 ,0 ); // curent hp

    // drawBox(window, XPBox, positon.x +120, positon.y - 120 +60, 150, 50, 76, 154 ,42 ); // xp
    // background if (xp < 0)
    // {
    //     drawBox(window, CurrentXPBox, positon.x +120,  positon.y - 120, 150 * (xp / maxXP), 50,
    //     118, 186 ,27 ); // current xp
    // }
    // else
    // {
    //     drawBox(window, CurrentXPBox, positon.x +120, positon.y - 120, 0.1, 50, 118, 186 ,27 );
    //     // current xp
    // }
}

void Player::drawBox(sf::RenderWindow *window,
                     sf::RectangleShape box,
                     float boxPosX,
                     float boxPosY,
                     float boxWidth,
                     float boxheight,
                     int r,
                     int g,
                     int b)

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