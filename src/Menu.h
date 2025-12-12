#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <optional>
#include <vector>

#include "GameState.h"

// Learned about optionals on cpp
struct ElementsInfo
{
    sf::String text;
    float xAlignn;
    float yAlign;
    std::optional<std::function<void()>> onClick = std::nullopt;
    std::optional<int> fontSize = std::nullopt;
};

class Menu
{
  public:
    Menu(std::vector<ElementsInfo> const &elements, bool windowOpen);
    virtual ~Menu() = default;

    void draw(sf::RenderWindow *window) const;
    virtual bool handleEvent(sf::Event event);
    bool isOpen() const;

  protected:
    void setIsOpen(bool isOpen);
    void setButtons(std::vector<ElementsInfo> const &elements);
    virtual std::vector<ElementsInfo> createButtons() const = 0;

  private:
    void focusButton(int index);
    void unFocusButton(int index);

    void changeFocusedIdx(int change);

    sf::Font defaultFont;
    std::vector<ElementsInfo> buttonInfos;
    std::vector<sf::Text> textElements;
    std::vector<sf::Text> buttonElements;

    bool menuOpen;
    int focusedButtonIdx;
};

#endif