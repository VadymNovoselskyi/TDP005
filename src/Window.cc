#include "Window.h"

#include <iostream>

#include "StateMachine.h"

int const Window::WINDOW_WIDTH{1024};
int const Window::WINDOW_HEIGHT{768};
std::string const Window::GAME_TITLE{"THE GAME"};

Window::Window(std::vector<Menu *> const &menus, sf::Texture const *bgTexture)
    : window{new sf::RenderWindow{sf::VideoMode(Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT),
                                  Window::GAME_TITLE}},
      windowClosed{false}, menus{menus}, map{map}, bg{new sf::RectangleShape{}}
{
    bg->setSize({static_cast<float>(Window::WINDOW_WIDTH * 4),
                 static_cast<float>(Window::WINDOW_HEIGHT * 4)});
    bg->setOrigin({static_cast<float>(Window::WINDOW_WIDTH * 2),
                   static_cast<float>(Window::WINDOW_HEIGHT * 2)});

    bg->setTexture(bgTexture);

    // You need to set the textureRect for the repeat on texture to work
    // https://stackoverflow.com/questions/26517066/repeating-texture-to-fit-certain-size-in-sfml
    bg->setTextureRect({Window::WINDOW_WIDTH * 2,
                        Window::WINDOW_HEIGHT * 2,
                        Window::WINDOW_WIDTH * 2,
                        Window::WINDOW_HEIGHT * 2});
}

Window::~Window()
{
    // std::cout << "Running the window destructor" << std::endl;
    delete window;
    delete map;
    delete bg;
    window = nullptr;
    map = nullptr;
    bg = nullptr;

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
    window->draw(*bg);

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