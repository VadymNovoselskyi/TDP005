#include <iostream>
#include <vector>

#include "StateMachine.h"
#include "Menu.h"
#include "Menus.h"

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