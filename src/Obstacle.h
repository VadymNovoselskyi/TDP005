#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Entity.h"

class Obstacle : public Entity
{
  public:
    // Entity(std::string const &tag, sf::Vector2f const &pos);
    Obstacle(sf::Texture const *texture,
             sf::Vector2f position,
             std::string const &tag = "obstacle");

    void onCollision(Entity *other) override;
    void move() override;
    void draw(sf::RenderWindow *window) const override;
};

#endif