#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
  public:
    Projectile(sf::Vector2f const &pos, sf::Vector2f const &dir, double velocity, double damage);
    void onCollision(std::string const &other) override;

    void move() override;
    void draw(sf::RenderWindow *window) const override;

  private:
    double velocity;
    sf::Vector2f dir;
    double damage;
    sf::Texture const *texture;
};

#endif