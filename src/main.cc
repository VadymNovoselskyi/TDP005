#include <iostream>
#include <vector>

#include "GameStateMachine.h"
#include "Menu.h"
#include "Menus.h"

int main()
{
    auto gsm = GameStateMachine::init(nullptr);
    std::vector<Menu *> menus{};
    menus.push_back(new StartMenu());

    // std::cout << "Created the GameOverMenu" << std::endl;

    auto window = new Window(menus);

    // std::cout << "Created the GameStateMachine" << std::endl;
    gsm->setWindow(window);
    gsm->run();
    // std::cout << "Ran the GameStateMachine" << std::endl;

    GameStateMachine::deleteInstance();

    for (auto menu : menus)
    {
        delete menu;
    }
    return 0;
}