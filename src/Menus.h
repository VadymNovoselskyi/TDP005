#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "GameState.h"
#include "Menu.h"
#include "StateMachine.h"

class StartMenu : public Menu
{
  public:
    StartMenu();

  private:
    std::vector<ElementsInfo> createButtons() const override;
};

class PauseMenu : public Menu
{
  public:
    PauseMenu();

  private:
    std::vector<ElementsInfo> createButtons() const override;
};

class GameOverMenu : public Menu
{
  public:
    GameOverMenu();

  private:
    std::vector<ElementsInfo> createButtons() const override;
};

#endif