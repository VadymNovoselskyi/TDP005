#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "GameState.h"
#include "StateMachine.h"
#include "Menu.h"

class StartMenu : public Menu
{
  public:
    StartMenu();

  private:
    std::vector<ElementsInfo> createButtons() const override;
};

#endif