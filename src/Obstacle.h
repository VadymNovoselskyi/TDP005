#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Entity.h"

/**
 * Static obstacle entity that blocks space in the map
 *
 * Obstacle is responsible for:
 * - Holding a sprite and position for map obstacles
 * - Drawing itself as part of the entity list
 * - Being treated as a collision target for other entities
 */
class Obstacle : public Entity
{
  public:
    /**
     * Create an obstacle entity
     *
     * @param texture Texture to use for the obstacle sprite
     * @param position World position for the obstacle
     * @param tag Entity tag, defaults to "obstacle"
     */
    Obstacle(sf::Texture const *texture,
             sf::Vector2f position,
             std::string const &tag = "obstacle");

    /**
     * Does nothing (obstacles don't move)
     */
    void move() override;

    /**
     * Draw the obstacle sprite
     *
     * @param window The RenderWindow to draw into
     */
    void draw(sf::RenderWindow *window) const override;

    /**
     * Does nothing (obstacles don't die)
     */
    void die() override;

    /**
     * Does nothing (obstacles don't collide with other entities)
     *
     * @param other The entity this obstacle collided with
     */
    void onCollision(Entity *other) override;

    /**
     * Does nothing (obstacles don't collide with the border)
     */
    void onBorderCollision() override;
};

#endif