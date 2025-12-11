#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>
// to lower classes
#include <cmath>

#include "TextureManager.h"

class Entity : public sf::Sprite
{
  public:

    Entity(std::string const &tag, sf::Vector2f const &pos, double hp);
    virtual void onCollision(Entity *other) = 0;
    std::string getTag() const;
    virtual void move() = 0;

    virtual void draw(sf::RenderWindow *window) const;
    void takeDamage(double damage);

  protected:
    double hp;
    virtual void die() = 0;

  private:
    std::string tag;

    // The solution to -Woverloaded-virtual of draw from ::Drawable
    // Could also use the 'using', but do not want to expose the wrong method
    // https://stackoverflow.com/questions/9995421/gcc-woverloaded-virtual-warnings
    using sf::Drawable::draw;
};

#endif