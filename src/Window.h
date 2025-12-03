#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

class Window
{
  public:
    Window();
    ~Window();
    void draw();
    bool isClosed();

  private:
    int static const WIDTH;
    int static const HEIGHT;
    std::string static const GAME_TITLE;

    sf::RenderWindow *window;
    bool windowClosed;
};

#endif