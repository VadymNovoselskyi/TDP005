#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

#include "GameState.h"

struct ButtonInfo
{
    sf::String text;
    float x;
    float y;
    std::function<void()> onClick;
};

class Menu
{
  public:
    Menu(std::vector<ButtonInfo> buttons, bool windowOpen);
    virtual ~Menu();

    void draw(sf::RenderWindow *window) const;
    void handleEvent(sf::Event event);
    bool isOpen() const;

  protected:
    virtual std::vector<ButtonInfo> createButtons() const = 0;
    void setIsOpen(bool isOpen);

  private:
    void changeFocusedIdx(int change);

    sf::Font defaultFont;
    std::vector<ButtonInfo> buttons;
    std::vector<sf::Text *> buttonElements;

    bool menuOpen;
    int focusedButtonIdx;
};

#endif