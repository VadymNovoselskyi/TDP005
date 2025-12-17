#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Map.h"
#include "Menu.h"

/**
 * Owns the RenderWindow and handles event and draw loops
 *
 * Window is responsible for:
 * - Creating and owning the RenderWindow
 * - Polling and sending events to menus
 * - Drawing tiles, map entities, highscore, and menus each frame
 * - Providing window size and RenderWindow pointer
 */
class Window
{
  public:
    /**
     * Get the Window singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton Window instance
     * @throws std::logic_error if the Window has not been initialized
     */
    static Window *instance();

    /**
     * Create and initialize the Window singleton
     *
     * @return Pointer to the created singleton Window instance
     */
    static Window *init();

    /**
     * Destroy the Window singleton instance
     */
    static void deleteInstance();

    /**
     * Set menus to the Window
     *
     * @param menus Menus to set to the Window
     */
    void setMenus(std::vector<Menu *> const &menus);

    /**
     * Poll window events and forward them to menus if not closing
     */
    void handleEvents();

    /**
     * Draw one frame
     */
    void draw();

    /**
     * Close the window and mark it as closed
     */
    void closeWindow();

    /**
     * Get the underlying SFML RenderWindow pointer
     *
     * @return Pointer to the RenderWindow
     */
    sf::RenderWindow *getRenderWindow() const;

    /**
     * Check if the window has been closed
     *
     * @return true if the window is closed
     */
    bool isClosed() const;

    /**
     * Get the window size
     *
     * @return Window size in pixels
     */
    static sf::Vector2u getWindowSize();

    /**
     * Get the default window height
     * Get the current window width
     *
     * @return Window width in pixels
     */
    static int getWindowWidth();

    /**
     * Get the current window height
     *
     * @return Window height in pixels
     */
    static int getWindowHeight();

  private:
    /**
     * Create a Window
     */
    Window();

    /**
     * Destroy the Window and delete owned resources
     */
    ~Window();
    static Window *instancePtr;

    std::string static const GAME_TITLE;

    sf::RenderWindow *window;
    bool windowClosed;

    std::vector<Menu *> menus;
};

#endif