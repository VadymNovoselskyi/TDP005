#include "Menu.h"

#include <iostream>

#include "Window.h"

Menu::Menu(std::vector<ElementsInfo> const &elements, bool windowOpen)
    : defaultFont{}, buttonInfos{}, textElements{}, buttonElements{}, menuOpen{windowOpen},
      focusedButtonIdx{0}
{
    defaultFont.loadFromFile("static/Orbitron-Bold.ttf");
    setButtons(elements);
}

Menu::~Menu()
{
    // std::cout << "Running the menu destructor" << std::endl;
    // for (auto buttonEl : buttonElements)
    // {
    //     delete buttonEl;
    // }
    // for (auto textEl : textElements)
    // {
    //     delete textEl;
    // }
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
        window->draw(buttonEl);
    }
    for (auto const &textEl : textElements)
    {
        window->draw(textEl);
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
            if (!buttonElements.empty() && focusedButtonIdx < static_cast<int>(buttonInfos.size()))
            {
                buttonInfos.at(focusedButtonIdx).onClick->operator()();
            }
            return true;
        default:
            return false;
        }
    }
    return false;
}

void Menu::setButtons(std::vector<ElementsInfo> const &elements)
{
    buttonElements.clear();
    textElements.clear();
    buttonInfos.clear();

    for (auto &elementInfo : elements)
    {
        sf::Text element{sf::Text(elementInfo.text, defaultFont, 50)};
        auto textRect{element.getGlobalBounds()};
        element.setOrigin(textRect.width / 2, textRect.height / 2);
        element.setPosition((Window::WINDOW_WIDTH * elementInfo.xAlignn),
                            (Window::WINDOW_HEIGHT * elementInfo.yAlign));

        element.setOutlineColor(sf::Color::Green);
        element.setOutlineThickness(4.0);

        if (!elementInfo.onClick.has_value())
        {
            element.setFillColor(sf::Color::Blue);
            textElements.push_back(element);
        }
        else
        {
            element.setFillColor(sf::Color::Blue);
            buttonInfos.push_back(elementInfo);
            buttonElements.push_back(element);
        }
    }
    if (!buttonElements.empty())
    {
        focusedButtonIdx = 0;
        focusButton(0);
    }
}

void Menu::focusButton(int index)
{
    sf::Text &button = buttonElements.at(index);
    button.setFillColor(sf::Color::Red);
}
void Menu::unFocusButton(int index)
{
    sf::Text &button = buttonElements.at(index);
    button.setFillColor(sf::Color::Blue);
}

void Menu::changeFocusedIdx(int change)
{
    if (buttonElements.empty())
    {
        return;
    }
    int targetIndex = (focusedButtonIdx + change) % buttonElements.size();

    unFocusButton(focusedButtonIdx);
    focusedButtonIdx = targetIndex;
    focusButton(focusedButtonIdx);
}

bool Menu::isOpen() const
{
    return menuOpen;
}

void Menu::setIsOpen(bool isOpen)
{
    menuOpen = isOpen;
    if (!buttonElements.empty())
    {
        unFocusButton(focusedButtonIdx);
        focusedButtonIdx = 0;
        focusButton(focusedButtonIdx);
    }
}