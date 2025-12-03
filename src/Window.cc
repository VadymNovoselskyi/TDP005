#include "Window.h"

int const Window::WIDTH{1024};
int const Window::HEIGHT{768};
std::string const Window::GAME_TITLE{"THE GAME"};

Window::Window() : window{}, windowClosed{false}
{
    this->window =
        new sf::RenderWindow{sf::VideoMode(Window::WIDTH, Window::HEIGHT), Window::GAME_TITLE};
}

Window::~Window()
{
    delete window;
    window = nullptr;
}

void Window::draw()
{
    sf::Event event{};
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            windowClosed = true;
        }
    }
}

bool Window::isClosed()
{
    return windowClosed;
}