#include "Window.h"

#include <iostream>

#include "StateMachine.h"

int const Window::WINDOW_WIDTH{1024};
int const Window::WINDOW_HEIGHT{768};
std::string const Window::GAME_TITLE{"THE GAME"};

Window::Window(std::vector<Menu *> const &menus, sf::Texture const *bgTexture)
    : window{new sf::RenderWindow{sf::VideoMode(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT),
                                  Window::GAME_TITLE}},
      windowClosed{false}, menus{menus}, bgTexture{bgTexture}
{
}

Window::~Window()
{
    // std::cout << "Running the window destructor" << std::endl;
    delete window;
    window = nullptr;

    for (auto menu : menus)
    {
        delete menu;
    }
}

void Window::handleEvents()
{
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
            bool handled = menu->handleEvent(event);
            if (handled)
            {
                break;
            }
        }
    }
}

void Window::draw()
{
    window->clear();

    sf::RectangleShape bg{window->getView().getSize()};
    bg.setPosition(0, 0);
    bg.setTexture(bgTexture);
    window->draw(bg);

    if (StateMachine::instance()->state() == GameState::IN_GAME)
    {
        Map::instance()->draw(window);
    }
    else
    {
        window->setView(window->getDefaultView());
        for (auto menu : menus)
        {
            menu->draw(window);
        }
    }

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