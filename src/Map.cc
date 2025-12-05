#include "Map.h"

#include <iostream>

#include "StateMachine.h"

Map::Map(Player const *player) : player{player}
{
}

Map::~Map()
{
    // std::cout << "Running the window destructor" << std::endl;
    delete player;
    player = nullptr;
}

void Map::draw(sf::RenderWindow *window) const
{
    if (StateMachine::instance()->state() != GameState::IN_GAME)
    {
        return;
    }

    std::cout << "Rendering the player" << std::endl;
    // player->dra;
}
