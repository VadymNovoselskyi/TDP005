#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>

#include "ExperienceManager.h"
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

class ChooseNameMenu : public Menu
{
  public:
    ChooseNameMenu();
    bool handleEvent(sf::Event event) override;
    // using Menu::setButtons;

  private:
    std::vector<ElementsInfo> createButtons() const override;
    std::vector<ElementsInfo> createButtons(std::string const &username) const;

    std::string username;
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