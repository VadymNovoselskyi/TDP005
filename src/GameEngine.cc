#include "GameEngine.h"

#include <iostream>
#include <vector>

#include "ExperienceManager.h"
#include "Highscore.h"
#include "Leaderboard.h"
#include "Menus.h"
#include "Spawner.h"
#include "TextureManager.h"
#include "TileManager.h"

int const GameEngine::FPS{60};
sf::Time const GameEngine::UPDATE_INTERVAL{sf::milliseconds(1000.0 / GameEngine::FPS)};

GameEngine::GameEngine() : window{}, spawner{}, clock{}
{
    // Init the StateMachine, TextureManager, Map and the menus
    StateMachine::init();
    TextureManager::init();
    Highscore::init(60);
    Leaderboard::init("static/leaderboard.txt");
    TileManager::init("static/tileMap.txt");

    std::vector<Menu *> menus{};
    auto levelUpMenu{new LevelUpMenu()};
    menus.push_back(new StartMenu());
    menus.push_back(new LeaderboardMenu());
    menus.push_back(new ChooseNameMenu());
    menus.push_back(new PauseMenu());
    menus.push_back(new GameOverMenu());
    menus.push_back(levelUpMenu);

    auto mapDimensions{TileManager::instance()->getMapDimensions()};
    auto mapCenter{sf::Vector2f{mapDimensions.x / 2.0f, mapDimensions.y / 2.0f}};

    Player *player{new Player(100.0,
                              10,
                              mapCenter,
                              "player",
                              [levelUpMenu](std::vector<LevelUpInfo> const &levelUpInfo)
                              { levelUpMenu->createOptions(levelUpInfo); })};

    Map::init(player, TileManager::instance()->getObstacles());
    spawner = new Spawner(player);

    // Init the menu and add exit listener
    window = new Window(menus);

    StateMachine::instance()->addListener("onStart",
                                          [player, mapCenter, this](GameState gameState)
                                          {
                                              if (gameState == GameState::STARTING_GAME)
                                              {
                                                  player->resetState(mapCenter);
                                                  spawner->resetState();
                                                  Map::instance()->resetState();
                                                  Highscore::instance()->saveHighscore();
                                                  Highscore::instance()->resetState();

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
                                                  Highscore::instance()->saveHighscore();
                                                  Leaderboard::instance()->saveLeaderboard(
                                                      "static/leaderboard.txt");
                                                  window->closeWindow();
                                              }
                                          });
}

GameEngine::~GameEngine()
{
    Map::deleteInstance();
    StateMachine::deleteInstance();
    TextureManager::deleteInstance();

    delete window;
    delete spawner;
    window = nullptr;
    spawner = nullptr;
}

void GameEngine::run()
{
    while (!window->isClosed())
    {
        clock.restart();
        window->handleEvents();

        if (StateMachine::instance()->state() == GameState::IN_GAME)
        {
            spawner->spawnEnemies();
            Map::instance()->handelUpdate(window->getRenderWindow());
        }
        window->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        // std::cout << "FPS: " << (1000.0 / delta.asMilliseconds()) << std::endl;
        sf::sleep(delta);
    }
}
