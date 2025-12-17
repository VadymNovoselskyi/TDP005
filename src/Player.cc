#include "Player.h"

#include <iostream>

#include "StateMachine.h"
#include "TextureManager.h"
#include "WeaponsManager.h"
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

Player::Player(double startHp,
               int startSpeed,
               sf::Vector2f const &position,
               std::string const &tag,
               std::function<void(std::vector<LevelUpInfo>)> const &onLevelUp)
    : Character(tag, startHp, startSpeed, position), startHp{startHp}, maxHp{startHp},
      startSpeed{startSpeed}, damageMultiplier{1}, rotation{}, oldPosition{position}, expManager{},
      weaponsManager{}, onLevelUp{onLevelUp}
{
    auto texture{TextureManager::instance()->getTexture("player.png")};
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);

    // Set the start value for player stats
    expManager.setCallbacks({{LevelUpChoice::HP,
                              [this]()
                              {
                                  increaseMaxHp(60);
                                  heal(40);
                                  StateMachine::instance()->continueGame();
                              }},
                             {LevelUpChoice::SPEED,
                              [this]()
                              {
                                  increaseSpeed(3);
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
                                  weaponsManager.receiveRandomWeapon();
                                  StateMachine::instance()->continueGame();
                              }}});
    weaponsManager.receiveNewWeapon("AR");
}

void Player::resetState(sf::Vector2f const &newPosition)
{
    Character::hp = startHp;
    maxHp = startHp;
    Character::movementSpeed = startSpeed;

    rotation = 0;
    damageMultiplier = 1;

    Entity::setPosition(newPosition);
    oldPosition = newPosition;

    expManager.resetState();
    weaponsManager.resetState();
    weaponsManager.receiveNewWeapon("AR");
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

    weaponsManager.setWeaponsPos(sf::Sprite::getPosition());
    weaponsManager.shoot();
}
sf::Vector2f Player::getOldPosition() const
{
    return oldPosition;
}
void Player::updateRotation(sf::RenderWindow *window) 
{
    // kollade upp om det fans någon atan funktion och hittad:
    // https://cppreference.com/w/c/numeric/math/atan2.html kollade upp hur jag skulle räkna
    // enhetscirklen:
    // https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-1/trigonometri/enhetscirkeln#!/
    double rotationRadians =
        std::atan2((sf::Mouse::getPosition(*window).y - (Window::getWindowHeight() / 2)),
                   (sf::Mouse::getPosition(*window).x - (Window::getWindowWidth() / 2)));
    rotation = rotationRadians * (180 / M_PI) + 90; // transform radians to rotation

    sf::Sprite::setRotation(rotation);
    weaponsManager.setWeaponsRotation(sf::Sprite::getRotation());
}

void Player::gainXp(int xp)
{
    bool lvlGained = expManager.gainXp(xp);
    if (!lvlGained)
    {
        return;
    }

    onLevelUp(expManager.chooseLevelUps(weaponsManager.canGetNewWeapon()));
    StateMachine::instance()->startLevelUp();
}

void Player::onCollision(Entity *other)
{
    if (other->getTag() == "obstacle")
    {
        sf::Sprite::setPosition(oldPosition);
    }
}

void Player::onBorderCollision()
{
    sf::Sprite::setPosition(oldPosition);
}

// methods to increase amount
void Player::heal(double amount)
{
    hp += amount;
}

void Player::increaseMaxHp(double hp)
{
    maxHp += hp;
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
    StateMachine::instance()->finishGame();
}

void Player::drawInfo(sf::RenderWindow *window)
{
    drawBox(window, // curent hp
            hpBox,
            sf::Sprite::getPosition().x - (Window::getWindowWidth() / 2.0) + BOX_OFFSET,  // x
            sf::Sprite::getPosition().y - (Window::getWindowHeight() / 2.0) + BOX_OFFSET, // y
            BOX_WIDHT,                                                                    // widht
            BOX_HEIGTH,                                                                   // heiht
            CURRENT_HP_BOX_COLLOR);                                                       // color
    drawBox(window,
            currentHpBox,
            sf::Sprite::getPosition().x - (Window::getWindowWidth() / 2.0) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::getWindowHeight() / 2.0) + BOX_OFFSET,
            BOX_WIDHT * (hp / maxHp),
            BOX_HEIGTH,
            HP_BOX_COLOR);

    drawBox(window,
            xpBox,
            sf::Sprite::getPosition().x - (Window::getWindowWidth() / 2.0) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::getWindowHeight() / 2.0) + XP_BOX_Y_OFFSET,
            BOX_WIDHT,
            BOX_HEIGTH,
            CURRENT_XP_BOX_COLOR);
    drawBox(window,
            currentXpBox,
            sf::Sprite::getPosition().x - (Window::getWindowWidth() / 2.0) + BOX_OFFSET,
            sf::Sprite::getPosition().y - (Window::getWindowHeight() / 2.0) + XP_BOX_Y_OFFSET,
            BOX_WIDHT * expManager.getXpFilled(),
            BOX_HEIGTH,
            XP_BOX_COLOR); // xp background
}

void Player::drawBox(sf::RenderWindow *window,
                     sf::RectangleShape &box,
                     float const &boxPosX,
                     float const &boxPosY,
                     float const &boxWidth,
                     float const &boxheight,
                     sf::Color const &boxColor)

{
    box.setSize(sf::Vector2f(boxWidth, boxheight));
    box.setFillColor(boxColor);
    box.setPosition(boxPosX, boxPosY);
    window->draw(box);
}
