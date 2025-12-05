#include <iostream>
#include <vector>

#include "GameState.h"
#include "Map.h"
#include "Menu.h"
#include "Menus.h"
#include "Player.h"
#include "StateMachine.h"
#include "Window.h"

int main()
{
    // Init the StateMachine and the menus
    StateMachine::init();
    std::vector<Menu *> menus{};
    menus.push_back(new StartMenu());
    menus.push_back(new PauseMenu());
    menus.push_back(new GameOverMenu());

    Player *player{
        new Player(10, 10, 10, sf::Vector2f{100.0, 100.0}, sf::Vector2f{100.0, 100.0}, "Player1", 0, 0, 0, 0)};
    Map *map{new Map(player)};

    // Init the menu and add exit listener
    Window *window = new Window(menus, map);

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