#include <iostream>

#include "GameState.h"

int main()
{
    auto gs = new GameState();
    gs->run();

    delete gs;
    return 0;
}