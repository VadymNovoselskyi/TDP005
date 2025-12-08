#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include <functional>
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
    std::function<void()> onClick;
};

class LevelUpMenu : public Menu
{
  public:
    LevelUpMenu();
    void createOptions(std::vector<LevelUpInfo> const &levelUpOptions);
    using Menu::setButtons;

  private:
    std::vector<ElementsInfo> createButtons(std::vector<LevelUpInfo> const &levelUpOptions) const;
    std::vector<ElementsInfo> createButtons() const override;
};

#endif