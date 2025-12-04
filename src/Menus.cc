#include "Menus.h"

#include <iostream>

StartMenu::StartMenu() : Menu(createButtons())
{
}

std::vector<ButtonInfo> StartMenu::createButtons() const
{
    std::vector<ButtonInfo> buttons{};

    ButtonInfo startButton{
        "START", 200, 100, []() { std::cout << "Starting the game!" << std::endl; }};
    buttons.push_back(startButton);

    ButtonInfo rankingsButton{
        "RANKINGS", 200, 300, []() { std::cout << "Switching to rankings!" << std::endl; }};
    buttons.push_back(rankingsButton);

    ButtonInfo exitButton{
        "EXIT", 200, 500, []() { std::cout << "EXITING the game!" << std::endl; }};
    buttons.push_back(exitButton);

    return buttons;
}
