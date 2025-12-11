#include "EnemyProjectile.h"

#include <iostream>

EnemyProjectile::EnemyProjectile(sf::Vector2f const &pos, double rotation, double velocity, double damage)
    : Entity(std::string{"projectile"}, pos), velocity{velocity}, damage{damage},
      texture{TextureManager::instance()->getTexture("Enemy_bullet.png")}
{
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setRotation(rotation);
    sf::Sprite::setOrigin(sf::Sprite::getScale().x / 2, sf::Sprite::getScale().y / 2);
}

void EnemyProjectile::onCollision(std::string const &other)
{
    if (other == "player")
    {
        // other take damage
    }
}

void EnemyProjectile::move()
{
    sf::Vector2f dir{
        static_cast<float>(std::cos((sf::Sprite::getRotation() + 90) * M_PI / 180.0f)),
        static_cast<float>(std::sin((sf::Sprite::getRotation() + 90) * M_PI / 180.0f))};

    sf::Sprite::Transformable::move(-dir.x * velocity, -dir.y * velocity);
}

void EnemyProjectile::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    // Draw HP and XP too plz
}
