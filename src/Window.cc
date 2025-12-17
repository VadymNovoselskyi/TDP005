#include "Window.h"

#include "Highscore.h"
#include "TilesManager.h"

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

Window *Window::init()
{
    Window::instancePtr = new Window();
    return Window::instancePtr;
}
void Window::deleteInstance()
{
    delete Window::instancePtr;
    Window::instancePtr = nullptr;
}

Window::Window()
    : window{new sf::RenderWindow{
          sf::VideoMode::getDesktopMode(), Window::GAME_TITLE, sf::Style::Fullscreen}},
      windowClosed{false}, menus{}
{
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

sf::Vector2u Window::getWindowSize()
{
    return instancePtr->window->getSize();
}

int Window::getWindowWidth()
{
    return instancePtr->window->getSize().x;
}

int Window::getWindowHeight()
{
    return instancePtr->window->getSize().y;
}

void Window::setMenus(std::vector<Menu *> const &menus)
{
    this->menus = menus;
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
    TilesManager::instance()->drawTiles(window);

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