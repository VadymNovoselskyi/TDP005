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
