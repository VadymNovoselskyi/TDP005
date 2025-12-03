#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

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
    Menu(std::vector<ButtonInfo> buttons);
    virtual ~Menu() = default;

    void draw(sf::RenderWindow *window) const;
    void changeFocusedIndex(int change);
    void handleClick();

  protected:
    virtual std::vector<ButtonInfo> createButtons() const = 0;

  private:
    sf::Font defaultFont;
    std::vector<ButtonInfo> buttons;
    std::vector<sf::Text> buttonElements;

    int focusedButtonIdx;
};

#endif