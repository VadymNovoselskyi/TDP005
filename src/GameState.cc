#include "GameState.h"

#include "Window.h"

int const GameState::FPS{60};
sf::Time const GameState::UPDATE_INTERVAL{sf::milliseconds(1000.0 / FPS)};

GameState::GameState() : window{new Window()}
{
}

GameState::~GameState()
{
    delete window;
    window = nullptr;
}

void GameState::run()
{
    while (!window->isClosed())
    {
        clock.restart();
        window->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        sf::sleep(delta);
    }
}