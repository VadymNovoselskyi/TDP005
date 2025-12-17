#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

// to lower classes
#include <cmath>

#include "TextureManager.h"

/**
 * Entity
 *
 * Entity is responsible for:
 * - Heritage to the lower classes
 * - To not repeat kode in the lower classes
 */
class Entity : public sf::Sprite
{
  public:
    /**
     * Construct a Entity and populate it with tag, pos and hp
     * @param tag tag is a way to know what typ the entity is (witch typ of lower class)
     * @param pos position that sf::Sprite gets
     * @param hp hit points for the entity
     */
    Entity(std::string const &tag, sf::Vector2f const &pos, double hP);

    /**
     * getTag gives the tag
     * @return the tag as a std::string
     */
    std::string getTag() const;

    /**
     * Draw the entity
     * @param window The RenderWindow to draw into
     */
    virtual void draw(sf::RenderWindow *window) const;

    /**
     * Take away from hitPoints (hP) with the amount of damage
     *
     * @param damage Damage is how mutch you should take away from hitPoints (hP)
     */
    virtual void takeDamage(double damage);

    /**
     * Handel all sort of collison when map say that it have collided with other
     *
     * @param other a pointer to a Entity so the can interakt with itch other
     */
    virtual void onCollision(Entity *other) = 0;

    /**
     * Every Entity need it but reakt diffrently
     */
    virtual void onBorderCollision() = 0;
    /**
     * Every Entity need it but reakt diffrently
     */
    virtual void move() = 0;

  protected:
    double hp;

    /**
     * Every Entity need it but reakt diffrently
     */
    virtual void die() = 0;

  private:
    std::string tag;

    // The solution to -Woverloaded-virtual of draw from ::Drawable
    // Could also use the 'using', but do not want to expose the wrong method
    // https://stackoverflow.com/questions/9995421/gcc-woverloaded-virtual-warnings
    using sf::Drawable::draw;
};

#endif