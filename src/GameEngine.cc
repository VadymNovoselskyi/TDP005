#include "GameEngine.h"

#include <iostream>

#include "Menus.h"
#include "TextureManager.h"
#include "Spawner.h"

int const GameEngine::FPS{60};
sf::Time const GameEngine::UPDATE_INTERVAL{sf::milliseconds(1000.0 / GameEngine::FPS)};

GameEngine::GameEngine() : window{}, clock{}
{
    // Init the StateMachine, TextureManager, Map and the menus
    StateMachine::init();
    TextureManager::init();

    Player *player{new Player(
        10, 10, 10, sf::Vector2f{100.0, 100.0}, sf::Vector2f{100.0, 100.0}, "Player1", 0, 0, 0, 0)};
    Map::init(player);

    Spawner spawner{Spawner(5.0, player)};

    sf::Texture *bgTexture = TextureManager::instance()->getTexture("grass.png");
    bgTexture->setRepeated(true);

    std::vector<Menu *> menus{};

    menus.push_back(new StartMenu());
    menus.push_back(new PauseMenu());
    menus.push_back(new GameOverMenu());
    menus.push_back(new LevelUpMenu());

    // Init the menu and add exit listener
    window = new Window(menus, bgTexture);

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
                                          [this](GameState gameState)
                                          {
                                              if (gameState == GameState::EXIT)
                                              {
                                                  window->closeWindow();
                                              }
                                          });

    Map::instance()->addEntity(player);
}

GameEngine::~GameEngine()
{
    StateMachine::deleteInstance();
    TextureManager::deleteInstance();
    delete window;
    window = nullptr;
}

void GameEngine::run()
{
    while (!window->isClosed())
    {
        clock.restart();
        window->handleEvents();
        Map::instance()->handelUpdate();
        window->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        sf::sleep(delta);
    }
}
