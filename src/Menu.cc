#include "Menu.h"

#include "Window.h"

int const Menu::DEFAULT_FONT_SIZE{50};
float const Menu::DEFAULT_OUTLINE_THICKNESS{4.0F};
sf::Vector2f const Menu::DEFAULT_SHADOW_OFFSET{6.0F, 9.0F};
float const Menu::TRIANGLE_RADIUS{12.0f};
float const Menu::TRIANGLE_OFFSET{50.0F};

sf::Color const Menu::TEXT_COLOR{sf::Color::Blue};
sf::Color const Menu::UNFOCUSED_BUTTON_COLOR{sf::Color::Blue};
sf::Color const Menu::FOCUSED_BUTTON_COLOR{sf::Color::Red};
sf::Color const Menu::OUTLINE_COLOR{sf::Color::Green};

Menu::Menu(std::vector<ElementsInfo> const &elements, bool windowOpen)
    : defaultFont{}, buttonInfos{}, textElements{}, buttonElements{}, shadowElements{},
      leftTriangle{}, rightTriangle{},
      menuCenter{Window::getWindowWidth() / 2.0F, Window::getWindowHeight() / 2.0F},
      menuOpen{windowOpen}, focusedButtonIdx{0}
{
    defaultFont.loadFromFile("static/Orbitron-Bold.ttf");

    leftTriangle = sf::CircleShape(TRIANGLE_RADIUS, 3);
    leftTriangle.setFillColor(FOCUSED_BUTTON_COLOR);
    leftTriangle.setOrigin(TRIANGLE_RADIUS, TRIANGLE_RADIUS);
    leftTriangle.setRotation(90.0f); // Rotate to point right

    rightTriangle = sf::CircleShape(TRIANGLE_RADIUS, 3);
    rightTriangle.setFillColor(FOCUSED_BUTTON_COLOR);
    rightTriangle.setOrigin(TRIANGLE_RADIUS, TRIANGLE_RADIUS);
    rightTriangle.setRotation(-90.0f); // Rotate to point left

    setButtons(elements);
}

void Menu::draw(sf::RenderWindow *window)
{
    if (!menuOpen)
    {
        return;
    }

    auto viewCenter{window->getView().getCenter()};
    sf::Vector2f centerOffset{viewCenter - menuCenter};

    for (auto &shadowEl : shadowElements)
    {
        shadowEl.move(centerOffset);
        window->draw(shadowEl);
    }

    for (auto &buttonEl : buttonElements)
    {
        buttonEl.move(centerOffset);
        window->draw(buttonEl);
    }
    for (auto &textEl : textElements)
    {
        textEl.move(centerOffset);
        window->draw(textEl);
    }

    if (!buttonElements.empty())
    {
        updateTrianglesPositions();

        leftTriangle.move(centerOffset);
        rightTriangle.move(centerOffset);
        window->draw(leftTriangle);
        window->draw(rightTriangle);
    }

    menuCenter = viewCenter;
}

bool Menu::handleEvent(sf::Event const &event)
{
    if (!menuOpen)
    {
        return false;
    }

    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Up:
            changeFocusedIdx(-1);
            return true;

        case sf::Keyboard::Down:
            changeFocusedIdx(1);
            return true;

        case sf::Keyboard::Enter:
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
    shadowElements.clear();
    buttonInfos.clear();
    menuCenter = {Window::getWindowWidth() / 2.0F, Window::getWindowHeight() / 2.0F};

    for (auto &elementInfo : elements)
    {
        sf::Text element{sf::Text(
            elementInfo.text, defaultFont, elementInfo.fontSize.value_or(DEFAULT_FONT_SIZE))};
        auto textRect{element.getGlobalBounds()};
        element.setOrigin(textRect.width / 2, textRect.height / 2);
        element.setPosition((Window::getWindowWidth() * elementInfo.xAlignn),
                            (Window::getWindowHeight() * elementInfo.yAlign));

        element.setOutlineColor(OUTLINE_COLOR);
        element.setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);

        sf::Text shadow = element;
        shadow.setFillColor(sf::Color(0, 0, 0, 150));
        shadow.setOutlineColor(sf::Color(0, 0, 0, 150));
        shadow.move(DEFAULT_SHADOW_OFFSET);
        shadowElements.push_back(shadow);

        if (!elementInfo.onClick.has_value())
        {
            element.setFillColor(TEXT_COLOR);
            textElements.push_back(element);
        }
        else
        {
            element.setFillColor(UNFOCUSED_BUTTON_COLOR);
            buttonInfos.push_back(elementInfo);
            buttonElements.push_back(element);
        }
    }
    if (!buttonElements.empty())
    {
        focusedButtonIdx = 0;
        focusButton(0);
        updateTrianglesPositions();
    }
}

void Menu::focusButton(int index)
{
    sf::Text &button = buttonElements.at(index);
    button.setFillColor(FOCUSED_BUTTON_COLOR);
}
void Menu::unfocusButton(int index)
{
    sf::Text &button = buttonElements.at(index);
    button.setFillColor(UNFOCUSED_BUTTON_COLOR);
}

void Menu::changeFocusedIdx(int change)
{
    if (buttonElements.empty())
    {
        return;
    }
    int targetIndex = (focusedButtonIdx + change) % buttonElements.size();

    unfocusButton(focusedButtonIdx);
    focusedButtonIdx = targetIndex;
    focusButton(focusedButtonIdx);
    updateTrianglesPositions();
}

void Menu::updateTrianglesPositions()
{
    if (buttonElements.empty() || focusedButtonIdx < 0 ||
        focusedButtonIdx >= static_cast<int>(buttonElements.size()))
    {
        return;
    }

    sf::Text const &button = buttonElements.at(focusedButtonIdx);
    auto textRect = button.getGlobalBounds();
    float buttonCenterY = textRect.top + textRect.height / 2.0F;

    float leftTriangleX = textRect.left - TRIANGLE_OFFSET;
    leftTriangle.setPosition(leftTriangleX, buttonCenterY);

    float rightTriangleX = textRect.left + textRect.width + TRIANGLE_OFFSET;
    rightTriangle.setPosition(rightTriangleX, buttonCenterY);
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
        unfocusButton(focusedButtonIdx);
        focusedButtonIdx = 0;
        focusButton(focusedButtonIdx);
    }
}