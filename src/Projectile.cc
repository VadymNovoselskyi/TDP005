#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, double velocity, double damage)
    :Entity(std::string{"projectile"}, pos), velocity{velocity}, damage{damage}, texture{TextureManager::instance()->getTexture("AR_bullet.png")}
{
    sf::Sprite::setTexture(*texture);
}

void Projectile::onCollision(std::string other)
{
    if (other == "enemy")
    {
        //other take damage
    }
}

void Projectile::move()
{
    double x {};
    double y {-velocity};

    //calculate dir

    sf::Sprite::Transformable::move(x, y);
}

void Projectile::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    // Draw HP and XP too plz
}