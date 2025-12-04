#include "Menu.h"

#include <iostream>

#include "Window.h"

Menu::Menu(std::vector<ElementsInfo> const &elements, bool windowOpen)
    : defaultFont{}, buttonInfos{}, textElements{}, buttonElements{}, menuOpen{windowOpen},
      focusedButtonIdx{0}
{
    defaultFont.loadFromFile("static/Orbitron-Bold.ttf");
    for (auto &elementInfo : elements)
    {
        sf::Text *element{new sf::Text(elementInfo.text, defaultFont, 50)};
        auto textRect{element->getGlobalBounds()};
        element->setOrigin(textRect.width / 2, textRect.height / 2);
        element->setPosition((Window::WIDTH * elementInfo.xAlignn),
                             (Window::HEIGHT * elementInfo.yAlign));

        element->setOutlineColor(sf::Color::Green);
        element->setOutlineThickness(4.0);

        if (!elementInfo.onClick.has_value())
        {
            element->setFillColor(sf::Color::Blue);
            textElements.push_back(element);
        }
        else
        {
            element->setFillColor(buttonElements.size() == 0 ? sf::Color::Red : sf::Color::Blue);
            buttonInfos.push_back(elementInfo);
            buttonElements.push_back(element);
        }
    }
}

Menu::~Menu()
{
    // std::cout << "Running the menu destructor" << std::endl;
    for (auto buttonEl : buttonElements)
    {
        delete buttonEl;
    }
    for (auto textEl : textElements)
    {
        delete textEl;
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
    for (auto const &textEl : textElements)
    {
        window->draw(*textEl);
    }
}

bool Menu::handleEvent(sf::Event event)
{
    if (!menuOpen)
    {
        return false;
    }

    if (event.type == sf::Event::KeyPressed)
    {
        // std::cout << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() <<
        // std::endl;

        switch (event.key.scancode)
        {
        case sf::Keyboard::Scan::Up:
            // std::cout << "pageUp" << std::endl;
            changeFocusedIdx(-1);
            return true;

        case sf::Keyboard::Scan::Down:
            // std::cout << "pageDown" << std::endl;
            changeFocusedIdx(1);
            return true;

        case sf::Keyboard::Scan::Enter:
            // std::cout << "Enter" << std::endl;

            // A little bit of cpp syntax goes long way
            buttonInfos.at(focusedButtonIdx).onClick->operator()();
            return true;
        default:
            return false;
        }
    }
    return false;
}

void Menu::changeFocusedIdx(int change)
{
    int targetIndex = (focusedButtonIdx + change) % buttonElements.size();
    // std::cout << targetIndex << std::endl;

    auto focusedButtonEl = buttonElements.at(focusedButtonIdx);
    focusedButtonEl->setFillColor(sf::Color::Blue);

    focusedButtonIdx = targetIndex;
    focusedButtonEl = buttonElements.at(focusedButtonIdx);
    focusedButtonEl->setFillColor(sf::Color::Red);
}

bool Menu::isOpen() const
{
    return menuOpen;
}

void Menu::setIsOpen(bool isOpen)
{
    menuOpen = isOpen;
}