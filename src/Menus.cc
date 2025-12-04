#include "Menus.h"

#include <iostream>

#include "GameStateMachine.h"

StartMenu::StartMenu()
    : Menu(createButtons(), GameStateMachine::instance()->state() == GameState::START_MENU)
{
    GameStateMachine::instance()->addListener("Start menu",
                                              [this](GameState gameState)
                                              { setIsOpen(gameState == GameState::START_MENU); });
}

std::vector<ButtonInfo> StartMenu::createButtons() const
{
    std::vector<ButtonInfo> buttons{};

    ButtonInfo startButton{"START", 200, 100, []() { GameStateMachine::instance()->startGame(); }};
    buttons.push_back(startButton);

    // ButtonInfo rankingsButton{
    //     "RANKINGS", 200, 300, []() { GameStateMachine::instance()->startGame(); }};
    // buttons.push_back(rankingsButton);

    ButtonInfo exitButton{"EXIT", 200, 300, []() { GameStateMachine::instance()->exitGame(); }};
    buttons.push_back(exitButton);

    return buttons;
}
