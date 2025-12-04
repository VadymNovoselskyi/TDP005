#include "Menus.h"

#include <iostream>

#include "StateMachine.h"

StartMenu::StartMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::START_MENU)
{
    StateMachine::instance()->addListener("Start menu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::START_MENU); });
}

std::vector<ButtonInfo> StartMenu::createButtons() const
{
    std::vector<ButtonInfo> buttons{};

    // TODO: Change this to percent from middle on screen
    ButtonInfo startButton{"START", 200, 100, []() { StateMachine::instance()->startGame(); }};
    buttons.push_back(startButton);

    // ButtonInfo rankingsButton{
    //     "RANKINGS", 200, 300, []() { StateMachine::instance()->startGame(); }};
    // buttons.push_back(rankingsButton);

    ButtonInfo exitButton{"EXIT", 200, 300, []() { StateMachine::instance()->exitGame(); }};
    buttons.push_back(exitButton);

    return buttons;
}
