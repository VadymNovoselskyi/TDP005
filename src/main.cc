#include "GameEngine.h"

int main()
{
    GameEngine::init();
    GameEngine::instance()->run();
    GameEngine::deleteInstance();

    return 0;
}