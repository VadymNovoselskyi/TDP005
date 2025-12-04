#include "Menu.h"

#include <iostream>
#include <stdexcept>

Menu::Menu(std::vector<ButtonInfo> buttons, bool windowOpen)
    : defaultFont{}, buttons{buttons}, buttonElements{}, menuOpen{windowOpen}, focusedButtonIdx{0}
{
    defaultFont.loadFromFile("static/Orbitron-Bold.ttf");
    for (auto const &button : buttons)
    {
        sf::Text *buttonElement{new sf::Text(button.text, defaultFont, 50)};
        buttonElement->setPosition(button.x, button.y);
        buttonElement->setOutlineColor(sf::Color::Green);
        buttonElement->setFillColor(buttonElements.size() == 0 ? sf::Color::Blue : sf::Color::Red);
        buttonElement->setOutlineThickness(5.0);

        buttonElements.push_back(buttonElement);
    }
}

Menu::~Menu()
{
    // std::cout << "Running the menu destructor" << std::endl;
    for (auto buttonEl : buttonElements)
    {
        delete buttonEl;
    }
}

void Menu::draw(sf::RenderWindow *window) const
{
    // std::cout << "Running the draw loop in Menu" << std::endl;
    if (!menuOpen)
    {
        return;
    }

    for (auto const &buttonEl : buttonElements)
    {
        window->draw(*buttonEl);
    }
}

void Menu::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // std::cout << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() <<
        // std::endl;

        switch (event.key.scancode)
        {
        case sf::Keyboard::Scan::Up:
            // std::cout << "pageUp" << std::endl;
            changeFocusedIdx(-1);
            break;

        case sf::Keyboard::Scan::Down:
            // std::cout << "pageDown" << std::endl;
            changeFocusedIdx(1);
            break;

        case sf::Keyboard::Scan::Enter:
            // std::cout << "Enter" << std::endl;
            buttons.at(focusedButtonIdx).onClick();
            break;
        default:
            return;
        }
    }
}

void Menu::changeFocusedIdx(int change)
{
    if (change != -1 && change != 1)
    {
        throw std::logic_error("Invalid change for enu::changeFocusedIndex" + change);
    }
    int targetIndex = (focusedButtonIdx + change) % buttonElements.size();
    // std::cout << targetIndex << std::endl;

    auto focusedButtonEl = buttonElements.at(focusedButtonIdx);
    focusedButtonEl->setFillColor(sf::Color::Red);

    focusedButtonIdx = targetIndex;
    focusedButtonEl = buttonElements.at(focusedButtonIdx);
    focusedButtonEl->setFillColor(sf::Color::Blue);
}

bool Menu::isOpen() const
{
    return menuOpen;
}

void Menu::setIsOpen(bool isOpen)
{
    menuOpen = isOpen;
}