#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

// to lower classes
#include "TextureManager.h"
#include <cmath>

class Entity : public sf::Sprite
{
  public:
    Entity(std::string const &tag, sf::Vector2f const &pos);
    virtual void onCollision(std::string const &other ) = 0;
    std::string getTag() const;
    virtual void move() = 0;

    virtual void draw(sf::RenderWindow *window) const;

  private:
    std::string tag;

    // The solution to -Woverloaded-virtual of draw from ::Drawable
    // Could also use the 'using', but do not want to expose the wrong method
    // https://stackoverflow.com/questions/9995421/gcc-woverloaded-virtual-warnings
    using sf::Drawable::draw;
};

#endif