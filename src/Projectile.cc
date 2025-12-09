#include "Projectile.h"
#include <iostream>

Projectile::Projectile(sf::Vector2f const &pos, double rotation, double velocity, double damage)
    :Entity(std::string{"projectile"}, pos), velocity{velocity}, damage{damage}, texture{TextureManager::instance()->getTexture("AR_bullet.png")}
{
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setRotation(rotation);
    sf::Sprite::setOrigin(sf::Sprite::getScale().x / 2, sf::Sprite::getScale().y / 2);
}

void Projectile::onCollision(std::string const &other)
{
    if (other == "enemy")
    {
        // other take damage
    }
}

void Projectile::move()
{
    // sf::Sprite::Transformable::move(-std::cos(Transformable::getRotation()) * velocity, -std::sin(Transformable::getRotation()) * velocity);
    sf::Vector2f dir {std::cos((sf::Sprite::getRotation() + 90) * M_PI / 180.0f), std::sin((sf::Sprite::getRotation() + 90)  * M_PI / 180.0f)}; 
    // if(Transformable::getRotation() == 0)
    // {
    //     dir = {0, 1};
    // }
    // else if (Transformable::getRotation() == 45)
    // {
    //     dir = {-0.5f, 0.5f};
    // }
    // else if(Transformable::getRotation() == 90)
    // {
    //     dir = {-1, 0};
    // }
    // else if(Transformable::getRotation() == 135)
    // {
    //     dir = {-0.5f, -0.5f};
    // }
    // else if(Transformable::getRotation() == 180)
    // {
    //     dir = {0, -1};
    // }
    // else if(Transformable::getRotation() == 225)
    // {
    //     dir = {0.5f, -0.5f};
    // }
    // else if(Transformable::getRotation() == 270)
    // {
    //     dir = {1, 0};
    // }
    // else if(Transformable::getRotation() == 315)
    // {
    //     dir = {0.5f, 0.5f};
    // }
    sf::Sprite::Transformable::move(-dir.x * velocity, -dir.y * velocity);
}

void Projectile::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    // Draw HP and XP too plz
}
