#ifndef OBSTICLE_H
#define OBSTICLE_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Entity.h"

class Obsticle : public Entity
{
  public:
    // Entity(std::string const &tag, sf::Vector2f const &pos);
    Obsticle(sf::Texture texture, sf::Vector2f position);

    void onCollision(std::string const &other) override;
    void move() override;
    void draw(sf::RenderWindow *window) const override;
};

#endif