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
     * @param menus Menus owned by Window and used for event handling and drawing
     * @return Pointer to the created singleton Window instance
     */
    static Window *init(std::vector<Menu *> const &menus);

    /**
     * Destroy the Window singleton instance
     */
    static void deleteInstance();

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

    int static const DEFAULT_WINDOW_WIDTH;  
    int static const DEFAULT_WINDOW_HEIGHT;

  private:
    /**
     * Create a Window and take ownership of menus
     *
     * @param menus Menus owned by Window
     */
    Window(std::vector<Menu *> const &menus);

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