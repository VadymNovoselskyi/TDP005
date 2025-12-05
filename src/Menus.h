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
    bool handleEvent(sf::Event event) override;

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

struct LevelUpInfo
{
    std::string name;
    std::string description;
    // Change to the level up enum
    std::string levelUpValue;
};

class LevelUpMenu : public Menu
{
  public:
    LevelUpMenu(std::vector<LevelUpInfo> const &levelUpOptions);

  private:
    std::vector<ElementsInfo> createButtons(std::vector<LevelUpInfo> const &levelUpOptions) const;
};

#endif