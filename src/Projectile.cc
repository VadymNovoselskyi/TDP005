#include "Projectile.h"


Projectile::Projectile(sf::Vector2f const &pos, double velocity, double damage)
    :Entity(std::string{"projectile"}, pos), velocity{velocity}, damage{damage}, texture{TextureManager::instance()->getTexture("AR_bullet.png")}
{
    sf::Sprite::setTexture(*texture);
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
    double x {};
    double y {-velocity};

    if (std::abs(x) + std::abs(y) > 1)
    {
        x = x / std::sqrt(2);
        y = y / std::sqrt(2);

        // matematic explination:
        // https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-2/trigonometri/radianer#!/
        // used to check calculation with degrees

        if (y >= 0) // down
        {
            // multiplying by (180/PI)to convert radian to degrees and subtract to flip rotation.
            sf::Sprite::setRotation(180.f - std::asin(x) * (180.f / M_PI));
        }
        else // up
        {
            sf::Sprite::setRotation(std::asin(x) * (180.f / M_PI));
        }

    } // https://www.matteboken.se/lektioner/gymnasiet/matte-fortsattning-niva-1/trigonometri/enhetscirkeln#!/
      // - fixa rotaiton utifrån mus


    // calculate dir

    sf::Sprite::Transformable::move(x, y);
}

void Projectile::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    // Draw HP and XP too plz
}