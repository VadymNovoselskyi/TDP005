#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

/**
 * Declares the TextureManager singleton which owns all textures
 *
 * TextureManager is responsible for:
 * - Keeping a list of active textures
 * - Providing the texture by name
 */
class TextureManager
{
  public: // singelton taken from StateMachine
    /**
     * Get the TextureManager singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton TextureManager instance
     * @throws std::logic_error if the TextureManager has not been initialized
     */
    static TextureManager *instance();

    /**
     * Create and initialize the TextureManager singleton
     *
     * @return Pointer to the created singleton TextureManager instance
     */
    static TextureManager *init();

    /**
     * Destroy the TextureManager singleton instance and reset the stored pointer
     */
    static void deleteInstance();

    /**
     * Try to give you the image you have wrote in name from its vector and if it doesn't exist
     * there it add it to the vector and giv it
     *
     * @param name The name of the image with png or what sort it is
     * @return Texture so you can get a sprite
     */
    sf::Texture *getTexture(std::string const &name);

  private:
    static TextureManager *instancePtr;

    /**
     * Construct a TextureManager
     */
    TextureManager() = default;

    std::map<std::string, sf::Texture *> textureMap;
};

#endif