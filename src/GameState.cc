#include "GameState.h"

#include <iostream>

#include "Window.h"

int const GameState::FPS{1};
sf::Time const GameState::UPDATE_INTERVAL{sf::milliseconds(1000.0 / FPS)};

GameState::GameState(std::vector<Menu *> menus) : window{new Window(menus)}
{
    // std::cout << "Constructed the StartMenu" << std::endl;
}

GameState::~GameState()
{
    delete window;
    window = nullptr;
}

void GameState::run()
{
    // std::cout << "Running the GameOverState" << std::endl;
    while (!window->isClosed())
    {
        // std::cout << "Running the run loop" << std::endl;

        clock.restart();
        window->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        sf::sleep(delta);
    }
}