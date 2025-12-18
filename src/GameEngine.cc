#include "GameEngine.h"

#include <vector>

#include "ExperienceManager.h"
#include "Highscore.h"
#include "Leaderboard.h"
#include "Menus.h"
#include "Spawner.h"
#include "TextureManager.h"
#include "TilesManager.h"
#include "Window.h"

int const GameEngine::FPS{60};
sf::Time const GameEngine::UPDATE_INTERVAL{sf::milliseconds(1000.0 / GameEngine::FPS)};

GameEngine *GameEngine::instancePtr{nullptr};

GameEngine *GameEngine::instance()
{
    if (GameEngine::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init GameEngine before calling instance on it");
    }
    return GameEngine::instancePtr;
}

GameEngine *GameEngine::init()
{
    GameEngine::instancePtr = new GameEngine();
    return GameEngine::instancePtr;
}

void GameEngine::deleteInstance()
{
    delete GameEngine::instancePtr;
    GameEngine::instancePtr = nullptr;
}

GameEngine::GameEngine() : spawner{}, clock{}
{
    StateMachine::init();
    TextureManager::init();
    Highscore::init(FPS);
    Leaderboard::init("static/leaderboard.txt");
    TilesManager::init("static/tileMap.txt");
    Window::init();

    std::vector<Menu *> menus{};
    auto levelUpMenu{new LevelUpMenu()};
    auto leaderboardMenu{new LeaderboardMenu()};
    menus.push_back(new StartMenu());
    menus.push_back(leaderboardMenu);
    menus.push_back(new ChooseNameMenu());
    menus.push_back(new PauseMenu());
    menus.push_back(new GameOverMenu());
    menus.push_back(levelUpMenu);
    Window::instance()->setMenus(menus);

    auto mapCenter{TilesManager::instance()->getMapDimensions() / 2.0F};

    Player *player{new Player(100.0,
                              10,
                              mapCenter,
                              "player",
                              [levelUpMenu](std::vector<LevelUpInfo> const &levelUpInfo)
                              { levelUpMenu->createOptions(levelUpInfo); })};

    Map::init(player, TilesManager::instance()->getObstacles());
    spawner = new Spawner(player);

    // Resets the game states on each game start
    StateMachine::instance()->addListener(
        [player, mapCenter, this](GameState gameState)
        {
            if (gameState == GameState::STARTING_GAME)
            {
                player->resetState(mapCenter);
                spawner->resetState();
                Map::instance()->resetState();
                Highscore::instance()->resetState();

                StateMachine::instance()->setInGame();
            }
        });

    StateMachine::instance()->addListener(
        [leaderboardMenu](GameState gameState)
        {
            if (gameState == GameState::GAME_OVER)
            {
                Highscore::instance()->saveHighscore();
                leaderboardMenu->resetLeaderboard();
            }
        });

    StateMachine::instance()->addListener(
        [](GameState gameState)
        {
            if (gameState == GameState::EXIT)
            {
                Highscore::instance()->saveHighscore();
                Leaderboard::instance()->saveLeaderboard("static/leaderboard.txt");
                Window::instance()->closeWindow();
            }
        });
}

GameEngine::~GameEngine()
{
    Map::deleteInstance();
    StateMachine::deleteInstance();
    TextureManager::deleteInstance();

    delete spawner;
    spawner = nullptr;
}

void GameEngine::run()
{
    while (!Window::instance()->isClosed())
    {
        clock.restart();
        Window::instance()->handleEvents();

        if (StateMachine::instance()->state() == GameState::IN_GAME)
        {
            spawner->spawnEnemies();
            Map::instance()->handelUpdate(Window::instance()->getRenderWindow());
        }
        Window::instance()->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        sf::sleep(delta);
    }
}
