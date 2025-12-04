#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Menu.h"

class Window
{
  public:
    Window(std::vector<Menu *> const &menus);
    ~Window();
    void draw();
    void closeWindow();

    // .clang-tidy again
    [[nodiscard]] bool isClosed() const;

    int static const WIDTH;
    int static const HEIGHT;

  private:
    std::string static const GAME_TITLE;

    sf::RenderWindow *window;
    bool windowClosed;

    std::vector<Menu *> menus;
};

#endif