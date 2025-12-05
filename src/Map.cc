#include "Map.h"

#include <iostream>

#include "StateMachine.h"
#include "Window.h"

Map::Map(Player *player)
    : view{new sf::View{{Window::WINDOW_WIDTH / 2, Window::WINDOW_HEIGHT / 2},
                        {Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT}}},
      player{player}
{
}

Map::~Map()
{
    // std::cout << "Running the window destructor" << std::endl;
    delete player;
    player = nullptr;
}

void Map::draw(sf::RenderWindow *window) const
{
    if (StateMachine::instance()->state() != GameState::IN_GAME)
    {
        return;
    }
    player->move();

    // std::cout << "Rendering the player" << std::endl;
    view->setCenter(player->getPosition());
    window->setView(*view);
    player->draw(window);

    int const r{50};
    sf::CircleShape circle1{r};
    circle1.setOrigin(r, r);
    circle1.setFillColor(sf::Color::Red);
    sf::CircleShape circle2{r};
    circle2.setOrigin(r, r);
    circle2.setFillColor(sf::Color::Green);
    sf::CircleShape circle3{r};
    circle3.setOrigin(r, r);
    circle3.setFillColor(sf::Color::Blue);

    circle1.setPosition(500, 100);
    circle2.setPosition(1000, 100);
    circle3.setPosition(1500, 100);
    window->draw(circle1);
    window->draw(circle2);
    window->draw(circle3);
}
