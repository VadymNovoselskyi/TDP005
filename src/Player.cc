#include "Player.h"

#include <iostream>

#include "GameState.h"
#include "StateMachine.h"
#include "TextureManager.h"
#include "Window.h"
// variables that wont change and is used to make code easier to read
float const Player::BOX_OFFSET{18};
float const Player::XP_BOX_Y_OFFSET{78};
float const Player::BOX_WIDHT{150};
float const Player::BOX_HEIGTH{35};
// colors for each box, first is for the backgorund to show the amount that is lost or left
// the other box is to show the current amount
sf::Color const Player::HP_BOX_COLOR{204, 0, 0};
sf::Color const Player::CURRENT_HP_BOX_COLLOR{128, 0, 0};
sf::Color const Player::XP_BOX_COLOR{118, 186, 27};
sf::Color const Player::CURRENT_XP_BOX_COLOR{76, 154, 42};

Player::Player(double startHP,
               int startSpeed,
               sf::Vector2f const &position,
               std::string const &tag,
               int levels,
               std::function<void(std::vector<LevelUpInfo>)> const &onLevelUp)
    : Character(tag, startHP, startSpeed, position), startHP{startHP}, hp{startHP}, maxHP{startHP},
      startSpeed{startSpeed}, movementSpeed{startSpeed}, damageMultiplier{1}, rotation{},
      levels{levels}, onLevelUp{onLevelUp}, oldPosition{position}, expManager{}, weaponManager{}
{
    auto texture{TextureManager::instance()->getTexture("player.png")};
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
    // sets the start value for player stats

    expManager.setCallbacks({{LevelUpChoice::HP,
                              [this]()
                              {
                                  increaseMaxHP(100);
                                  StateMachine::instance()->continueGame();
                              }},
                             {LevelUpChoice::SPEED,
                              [this]()
                              {
                                  increaseSpeed(5);
                                  StateMachine::instance()->continueGame();
                              }},
                             {LevelUpChoice::DAMAGE,
                              [this]()
                              {
                                  increaseDamageMultiplyer(0.5);
                                  StateMachine::instance()->continueGame();
                              }},
                             {LevelUpChoice::WEAPON,
                              [this]()
                              {
                                  weaponManager.receiveRandomWeapon();
                                  StateMachine::instance()->continueGame();
                              }}});
    weaponManager.receiveNewWeapon("AR");
    weaponManager.receiveNewWeapon("Sniper");
}

void Player::move()
{
    // resets current direction and saves the old position
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
        // divides direction by std::sqrt(2) to get a lower speed when player goes diagonal
        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);
    }

    sf::Sprite::move(sf::Vector2f(direction.x * movementSpeed, direction.y * movementSpeed));

    weaponManager.setWeaponsPos(sf::Sprite::getPosition());
    weaponManager.shoot();
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
    rotation = rotationRadians * (180 / M_PI) + 90; // transform radians to rotation
    
    sf::Sprite::setRotation(rotation);
    weaponManager.setWeaponsRotation(sf::Sprite::getRotation());
}

void Player::gainXp(int xp)
{
    bool lvlGained = expManager.gainXp(xp);
    if (!lvlGained)
    {
        return;
    }

    onLevelUp(expManager.chooseLevelUps());
    StateMachine::instance()->startLevelUp();
}

void Player::onCollision(Entity *other)
{
    if (other->getTag() == "box")
    {
        sf::Sprite::setPosition(oldPosition);
    }
}
// methods to increase amount
void Player::heal(double amount)
{
    hp += amount;
}

void Player::increaseMaxHP(double hp)
{
    maxHP += hp;
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
    // reset xp, hp ,damage
    StateMachine::instance()->finishGame();
    sf::Sprite::move(sf::Vector2f(Window::WINDOW_WIDTH / 2, Window::WINDOW_HEIGHT / 2));
    hp = startHP;
    maxHP = startHP;
    movementSpeed = startSpeed;
    // ExperienceManager::resetxp();
    // waiting for method to remove every weapon exept start wepon
}
// methods to draw boxes
void Player::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    drawInfo(window);
}

void Player::drawInfo(sf::RenderWindow *window) const
{
    drawBox(window, // hp boxbackground -- fixa static const för ofset, fixa sf
            HPBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2.0) + BOX_OFFSET,  // x
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2.0) + BOX_OFFSET, // y
            BOX_WIDHT,                                                                // lenght
            BOX_HEIGTH,                                                               // widht
            HP_BOX_COLOR);                                                            // color
    drawBox(window,
            currentHPBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2.0) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2.0) + BOX_OFFSET,
            BOX_WIDHT * (hp / maxHP),
            BOX_HEIGTH,
            CURRENT_HP_BOX_COLLOR); // curent hp

    drawBox(window,
            xpBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2.0) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2.0) + XP_BOX_Y_OFFSET,
            BOX_WIDHT,
            BOX_HEIGTH,
            XP_BOX_COLOR); // xp background

    drawBox(window,
            currentXPBox,
            sf::Sprite::getPosition().x - (Window::WINDOW_WIDTH / 2.0) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::WINDOW_HEIGHT / 2.0) + XP_BOX_Y_OFFSET,
            BOX_WIDHT,
            BOX_HEIGTH,
            CURRENT_XP_BOX_COLOR);
    // current xp -- if sats om xp 0 = 0 - sätt längd 0 annars räkna ut
}

void Player::drawBox(sf::RenderWindow *window,
                     sf::RectangleShape box,
                     float boxPosX,
                     float boxPosY,
                     float boxWidth,
                     float boxheight,
                     sf::Color boxColor) const

{
    box.setSize(sf::Vector2f(boxWidth, boxheight));
    box.setFillColor(boxColor);
    box.setPosition(boxPosX, boxPosY);
    window->draw(box);
}
