#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>
#include <vector>

#include "GameState.h"

struct ElementsInfo
{
    sf::String text;
    float xAlignn;
    float yAlign;
    std::optional<std::function<void()>> onClick;
};

class Menu
{
  public:
    Menu(std::vector<ElementsInfo> const &elements, bool windowOpen);
    virtual ~Menu();

    void draw(sf::RenderWindow *window) const;
    bool handleEvent(sf::Event event);
    bool isOpen() const;

  protected:
    virtual std::vector<ElementsInfo> createButtons() const = 0;
    void setIsOpen(bool isOpen);

  private:
    void changeFocusedIdx(int change);

    sf::Font defaultFont;
    std::vector<ElementsInfo> buttonInfos;
    std::vector<sf::Text *> textElements;
    std::vector<sf::Text *> buttonElements;

    bool menuOpen;
    int focusedButtonIdx;
};

#endif