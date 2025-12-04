#include "Window.h"

#include <iostream>

int const Window::WIDTH{1024};
int const Window::HEIGHT{768};
std::string const Window::GAME_TITLE{"THE GAME"};

Window::Window(std::vector<Menu *> menus) : window{}, windowClosed{false}, menus{menus}
{
    // std::cout << "Constructed the Window" << std::endl;
    this->window =
        new sf::RenderWindow{sf::VideoMode(Window::WIDTH, Window::HEIGHT), Window::GAME_TITLE};
}

Window::~Window()
{
    delete window;
    window = nullptr;

    for (auto menu : menus)
    {
        delete menu;
    }
}

void Window::draw()
{
    // std::cout << "Running the draw" << std::endl;
    sf::Event event{};
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            closeWindow();
            return;
        }

        for (auto menu : menus)
        {
            menu->handleEvent(event);
        }
    }

    window->clear();
    // std::cout << menus.size() << std::endl;
    for (auto menu : menus)
    {
        // std::cout << "Running the draw for a menu" << std::endl;

        menu->draw(window);
    }
    // std::cout << "Completed running the draw" << std::endl;
    window->display();
}

void Window::closeWindow()
{
    window->close();
    windowClosed = true;
}

bool Window::isClosed() const
{
    return windowClosed;
}