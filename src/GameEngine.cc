#include "GameEngine.h"

#include <iostream>

#include "Menus.h"
#include "TextureManager.h"
#include "TileManager.h"
#include "WeaponManager.h"
#include "Spawner.h"

int const GameEngine::FPS{60};
sf::Time const GameEngine::UPDATE_INTERVAL{sf::milliseconds(1000.0 / GameEngine::FPS)};

GameEngine::GameEngine() : window{}, clock{}
{
    // Init the StateMachine, TextureManager, Map and the menus
    StateMachine::init();
    TextureManager::init();
    TileManager::init("static/tileMap.txt");
    WeaponManager::init();

    auto mapDimensions{TileManager::instance()->getMapDimensions()};
    Player *player{new Player(10.0,
                              10.0,
                              10,
                              sf::Vector2f{static_cast<float>(mapDimensions.x / 2.0),
                                           static_cast<float>(mapDimensions.y / 2.0)},
                              sf::Vector2f{0.0, 0.0},
                              "Player1",
                              0,
                              0)};
    Map::init(player, TileManager::instance()->getObstacles());
    Spawner spawner{Spawner(5.0, player)};

    std::vector<Menu *> menus{};

    menus.push_back(new StartMenu());
    menus.push_back(new ChooseNameMenu());
    menus.push_back(new PauseMenu());
    menus.push_back(new GameOverMenu());
    menus.push_back(new LevelUpMenu());

    // Init the menu and add exit listener
    window = new Window(menus);

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
    WeaponManager::instance()->getWeapon("AR");
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

        if (StateMachine::instance()->state() == GameState::IN_GAME)
        {
            Map::instance()->handelUpdate();
        }
        window->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        // std::cout << "FPS: " << (1000.0 / delta.asMilliseconds()) << std::endl;
        sf::sleep(delta);
    }
}
