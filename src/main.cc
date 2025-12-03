#include <iostream>
#include <vector>

#include "GameState.h"
#include "Menu.h"
#include "Menus.h"

int main()
{
    std::vector<Menu *> menus{};
    menus.push_back(new StartMenu());

    // std::cout << "Created the GameOverMenu" << std::endl;

    auto gs = new GameState(menus);
    // std::cout << "Created the GameState" << std::endl;
    gs->run();
    // std::cout << "Ran the GameState" << std::endl;

    delete gs;

    for (auto menu : menus)
    {
        delete menu;
    }
    return 0;
}