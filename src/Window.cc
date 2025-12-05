#include "Window.h"

#include <iostream>

#include "StateMachine.h"

int const Window::WINDOW_WIDTH{1024};
int const Window::WINDOW_HEIGHT{768};
std::string const Window::GAME_TITLE{"THE GAME"};

Window::Window(std::vector<Menu *> const &menus, Map *map)
    : window{new sf::RenderWindow{sf::VideoMode(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT),
                                  Window::GAME_TITLE}},
      windowClosed{false}, menus{menus}, map{map}
{
}

Window::~Window()
{
    // std::cout << "Running the window destructor" << std::endl;
    delete window;
    delete map;
    window = nullptr;
    map = nullptr;

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
            // std::cout << "Got close event" << std::endl;
            closeWindow();
            // std::cout << "Closed the window" << std::endl;
            return;
        }

        for (auto menu : menus)
        {
            bool handled = menu->handleEvent(event);
            if (handled)
            {
                break;
            }
        }
    }

    window->clear();
    map->draw(window);

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
    // std::cout << "Closing the window" << std::endl;
    window->close();
    windowClosed = true;
}

bool Window::isClosed() const
{
    return windowClosed;
}