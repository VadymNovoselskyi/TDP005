#include <iostream>
#include <vector>

#include "Menu.h"
#include "Menus.h"
#include "StateMachine.h"

int main()
{
    // Init the StateMachine and the menus
    StateMachine::init();
    std::vector<Menu *> menus{};
    menus.push_back(new StartMenu());
    menus.push_back(new PauseMenu());
    menus.push_back(new GameOverMenu());

    // Init the menu and add exit listener
    auto window = new Window(menus);

    // Should I do anything with STARTING_GAME and CONTINUING_GAME
    StateMachine::instance()->addListener("onStart",
                                          [](GameState gameState)
                                          {
                                              if (gameState == GameState::STARTING_GAME)
                                              {
                                                  StateMachine::instance()->setInGame();
                                              }
                                          });
    StateMachine::instance()->addListener("onContinue",
                                          [](GameState gameState)
                                          {
                                              if (gameState == GameState::CONTINUING_GAME)
                                              {
                                                  StateMachine::instance()->setInGame();
                                              }
                                          });
    StateMachine::instance()->addListener("onExit",
                                          [&window](GameState gameState)
                                          {
                                              if (gameState == GameState::EXIT)
                                              {
                                                  window->closeWindow();
                                              }
                                          });

    // Add main loop logic
    int const FPS{60};
    sf::Time const UPDATE_INTERVAL{sf::milliseconds(1000.0 / FPS)};
    sf::Clock clock{};

    while (!window->isClosed())
    {
        clock.restart();
        window->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        sf::sleep(delta);
    }

    StateMachine::deleteInstance();
    delete window;
    return 0;
}