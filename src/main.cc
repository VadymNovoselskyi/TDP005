#include <iostream>
#include <vector>

#include "GameEngine.h"

int main()
{
    GameEngine *gameEngine{new GameEngine()};
    gameEngine->run();
    delete gameEngine;
    
    return 0;
}