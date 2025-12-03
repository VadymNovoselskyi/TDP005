#include "Menu.h"

#include <iostream>
#include <stdexcept>

Menu::Menu(std::vector<ButtonInfo> buttons)
    : defaultFont{}, buttonElements{}, focusedButtonIdx{0}
{
    defaultFont.loadFromFile("static/Orbitron-Bold.ttf");

    for (auto const &button : buttons)
    {
        sf::Text buttonElement{button.text, defaultFont, 50};
        buttonElement.setPosition(button.x, button.y);
        buttonElement.setOutlineColor(sf::Color::Green);
        buttonElement.setFillColor(sf::Color::Red);
        buttonElement.setOutlineThickness(5.0);

        buttonElements.push_back(buttonElement);
    }
}

void Menu::draw(sf::RenderWindow *window) const
{
    // std::cout << "Running the draw loop in Menu" << std::endl;

    for (auto const &buttonEl : buttonElements)
    {
        window->draw(buttonEl);
    }
}

void Menu::changeFocusedIdx(int change)
{
    if (change != -1 && change != 1)
    {
        throw std::logic_error("Invalid change for enu::changeFocusedIndex" + change);
    }

    auto focusedButtonEl = buttonElements.at(focusedButtonIdx);
    focusedButtonEl.setFillColor(sf::Color::Red);

    focusedButtonIdx += change;
    focusedButtonEl = buttonElements.at(focusedButtonIdx);
    focusedButtonEl.setFillColor(sf::Color::Blue);
}
