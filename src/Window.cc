#include "Window.h"

#include <iostream>

#include "Highscore.h"
#include "TilesManager.h"

int const Window::DEFAULT_WINDOW_WIDTH{1024};
int const Window::DEFAULT_WINDOW_HEIGHT{768};
std::string const Window::GAME_TITLE{"THE GAME"};

Window *Window::instancePtr{nullptr};

Window *Window::instance()
{
    if (Window::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init Window before calling instance on it");
    }
    return Window::instancePtr;
}

Window *Window::init(std::vector<Menu *> const &menus)
{
    Window::instancePtr = new Window(menus);
    return Window::instancePtr;
}
void Window::deleteInstance()
{
    delete Window::instancePtr;
    Window::instancePtr = nullptr;
}

Window::Window(std::vector<Menu *> const &menus)
    : window{new sf::RenderWindow{
          sf::VideoMode(Window::DEFAULT_WINDOW_WIDTH, Window::DEFAULT_WINDOW_HEIGHT),
          Window::GAME_TITLE}},
      windowClosed{false}, menus{menus}
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

int Window::getWindowWidth()
{
    if (instancePtr == nullptr)
    {
        return DEFAULT_WINDOW_WIDTH;
    }
    return instancePtr->window->getSize().x;
}
int Window::getWindowHeight()
{
    if (instancePtr == nullptr)
    {
        return DEFAULT_WINDOW_HEIGHT;
    }
    return instancePtr->window->getSize().y;
}

sf::RenderWindow *Window::getRenderWindow() const
{
    return window;
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
    // TilesManager::instance()->drawTiles(window);

    Map::instance()->draw(window);
    Highscore::instance()->draw(window);

    for (auto menu : menus)
    {
        menu->draw(window);
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