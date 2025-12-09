#include "Player.h"

#include <iostream>

#include "StateMachine.h"
#include "TextureManager.h"
#include "Window.h"

float const Player::BOX_OFFSET{18};
float const Player::XP_BOX_Y_OFFSET{78};
sf::Color const Player::HP_BOX_COLOR{204, 0, 0};
sf::Color const Player::CURRENT_HP_BOX_COLLOR{128, 0, 0};
sf::Color const Player::XP_BOX_COLOR{118, 186, 27};
sf::Color const Player::CURRENT_XP_BOX_COLOR{76, 154, 42};

float static const START_HP = 100;

Player::Player(double startHP,
               int movementSpeed, 
               sf::Vector2f const &position,
               std::string const &tag,
               int levels,
               double damageMultiplier)
    : Character(tag, startHP, movementSpeed, position),
      levels{levels}, damageMultiplier{damageMultiplier}, oldPosition{position},
      texture{TextureManager::instance()->getTexture("player.png")}
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
    hp = startHP;
    maxHP = startHP;
}

void Player::move()
{
    sf::Vector2f direction;
    direction.x = 0;
    direction.y = 0;
    oldPosition = sf::Sprite::getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        direction.y = Direction::NORTH;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        direction.x = Direction::EAST;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        direction.y = Direction::SOUTH;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        direction.x = Direction::WEST;

    }
    if (std::abs(direction.x) + std::abs(direction.y) > 1)
    {
        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);

    } //

    sf::Sprite::move(sf::Vector2f(direction.x * movementSpeed, direction.y * movementSpeed));
}
void Player::updateRotation(sf::RenderWindow *window)
{
    // kollade upp om det fans någon atan funktion och hittad:
    // https://cppreference.com/w/c/numeric/math/atan2.html kollade upp hur jag skulle räkna
    // enhetscirklen:
    // https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-1/trigonometri/enhetscirkeln#!/
    double rotationRadians =
        std::atan2((sf::Mouse::getPosition(*window).y - (Window::WINDOW_HEIGHT / 2)),
                   (sf::Mouse::getPosition(*window).x - (Window::WINDOW_WIDTH / 2)));
    rotation = rotationRadians * (180 / M_PI) + 90; // transform radians to rtoation

    sf::Sprite::setRotation(rotation);
}

void Player::onCollision(std::string const &other)
{
    // if (other == "enemy")
    // {

    // }
    // if(other == "box")
    // {

    // }
}
void Player::heal(double amount)
{
    hp += amount;
}
void Player::increaseMaxHP(double amount)
{
    maxHP +=amount;
}
void Player::increaseSpeed(int amount)
{
    movementSpeed += amount;
}
void Player::increaseDamageMultiplyer(double amount)
{
    damageMultiplier += amount;
}

void Player::die()
{
    //reset xp, hp ,damage 
    StateMachine::instance()->finishGame();
}

void Player::draw(sf::RenderWindow *window)
{
    window->draw(*this);
    drawInfo(window);
}

void Player::drawInfo(sf::RenderWindow *window)
{

    drawBox(window, // hp boxbackground -- fixa static const för ofset, fixa sf
            HPBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2) + BOX_OFFSET,  // x
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2) + BOX_OFFSET, // y
            150,                                                                    // lenght
            35,                                                                     // widht
            HP_BOX_COLOR);                                                          // color
    drawBox(window,
            currentHPBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2) + BOX_OFFSET,
            150 * (hp / maxHP),
            35,
            CURRENT_HP_BOX_COLLOR); // curent hp

    drawBox(window,
            xpBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2) + XP_BOX_Y_OFFSET,
            150,
            35,
            XP_BOX_COLOR); // xp background

    drawBox(window,
            currentXPBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2) + XP_BOX_Y_OFFSET,
            0.1,
            35,
            CURRENT_XP_BOX_COLOR);
    // current xp -- if sats om xp 0 = 0 - sätt längd 0 annars räkna ut
}

void Player::drawBox(sf::RenderWindow *window,
                     sf::RectangleShape box,
                     float boxPosX,
                     float boxPosY,
                     float boxWidth,
                     float boxheight,
                     sf::Color boxColor)

{
    box.setSize(sf::Vector2f(boxWidth, boxheight));
    box.setFillColor(boxColor);
    box.setPosition(boxPosX, boxPosY);
    window->draw(box);
}
