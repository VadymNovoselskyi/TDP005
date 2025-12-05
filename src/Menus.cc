#include "Menus.h"

#include <iostream>

#include "StateMachine.h"

// Start menu
StartMenu::StartMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::IN_START_MENU)
{
    StateMachine::instance()->addListener("StartMenu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::IN_START_MENU); });
}

std::vector<ElementsInfo> StartMenu::createButtons() const
{
    std::vector<ElementsInfo> elements{};

    ElementsInfo title{"GAME NAME", 0.5, 0.1, std::nullopt};
    elements.push_back(title);

    ElementsInfo startButton{"START", 0.5, 0.4, []() { StateMachine::instance()->startGame(); }};
    elements.push_back(startButton);

    ElementsInfo rankingsButton{"RANKINGS", 0.5, 0.6, []() {}};
    // "RANKINGS", 0.5, 0.4, []() { StateMachine::instance()->startGame(); }};
    elements.push_back(rankingsButton);

    ElementsInfo exitButton{"EXIT", 0.5, 0.8, []() { StateMachine::instance()->exitGame(); }};
    elements.push_back(exitButton);

    return elements;
}

// Pause menu
PauseMenu::PauseMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::GAME_PAUSED)
{
    StateMachine::instance()->addListener("PauseMenu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::GAME_PAUSED); });
}

std::vector<ElementsInfo> PauseMenu::createButtons() const
{
    std::vector<ElementsInfo> elements{};

    ElementsInfo title{"GAME PAUSED", 0.5, 0.1, std::nullopt};
    elements.push_back(title);

    ElementsInfo continueButton{
        "CONTINUE", 0.5, 0.4, []() { StateMachine::instance()->continueGame(); }};
    elements.push_back(continueButton);

    ElementsInfo giveUpButton{
        "GIVE UP", 0.5, 0.6, []() { StateMachine::instance()->finishGame(); }};
    elements.push_back(giveUpButton);

    ElementsInfo exitButton{"EXIT", 0.5, 0.8, []() { StateMachine::instance()->exitGame(); }};
    elements.push_back(exitButton);

    return elements;
}

bool PauseMenu::handleEvent(sf::Event event)
{
    bool handled = Menu::handleEvent(event);
    if (handled)
    {
        return true;
    }

    if (StateMachine::instance()->state() == GameState::IN_GAME &&
        event.type == sf::Event::KeyPressed &&
        (event.key.scancode == sf::Keyboard::Scan::Space ||
         event.key.scancode == sf::Keyboard::Scan::Escape))
    {
        StateMachine::instance()->pauseGame();
        return true;
    }
    return false;
}

// Game Over menu
GameOverMenu::GameOverMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::GAME_OVER)
{
    StateMachine::instance()->addListener("GameOverMenu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::GAME_OVER); });
}

std::vector<ElementsInfo> GameOverMenu::createButtons() const
{
    std::vector<ElementsInfo> elements{};

    ElementsInfo title{"GAME OVER", 0.5, 0.1, std::nullopt};
    elements.push_back(title);

    ElementsInfo restartButton{
        "RESTART", 0.5, 0.4, []() { StateMachine::instance()->startGame(); }};
    elements.push_back(restartButton);

    ElementsInfo mainMenuButton{
        "MAIN MENU", 0.5, 0.6, []() { StateMachine::instance()->openStartMenu(); }};
    elements.push_back(mainMenuButton);

    ElementsInfo exitButton{"EXIT", 0.5, 0.8, []() { StateMachine::instance()->exitGame(); }};
    elements.push_back(exitButton);

    return elements;
}
