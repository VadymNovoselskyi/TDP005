#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Map.h"
#include "Menu.h"

class Window
{
  public:
    static Window *instance();
    static Window *init(std::vector<Menu *> const &menus);
    static void deleteInstance();

    void handleEvents();
    void draw();
    void closeWindow();
    sf::RenderWindow *getRenderWindow() const;
    bool isClosed() const;

    static int getWindowWidth();
    static int getWindowHeight();

    int static const DEFAULT_WINDOW_WIDTH;  
    int static const DEFAULT_WINDOW_HEIGHT;

  private:
    Window(std::vector<Menu *> const &menus);
    ~Window();
    static Window *instancePtr;

    std::string static const GAME_TITLE;

    sf::RenderWindow *window;
    bool windowClosed;

    std::vector<Menu *> menus;
};

#endif