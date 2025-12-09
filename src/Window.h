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
    Window(std::vector<Menu *> const &menus);
    ~Window();
    void handleEvents();
    void draw();
    void closeWindow();
    sf::RenderWindow* getRenderWindow() const;
    // .clang-tidy again
    [[nodiscard]] bool isClosed() const;

    int static const WINDOW_WIDTH;
    int static const WINDOW_HEIGHT;

  private:
    std::string static const GAME_TITLE;

    sf::RenderWindow *window;
    bool windowClosed;

    std::vector<Menu *> menus;
};

#endif