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

/**
 * Start menu shown when the game launches
 *
 * StartMenu is responsible for:
 * - Showing start button, leaderboard button, and exit button
 * - Listening to StateMachine and opening when in start menu state
 */
class StartMenu : public Menu
{
  public:
    StartMenu();

  private:
    /**
     * Create the menu elements for the start menu
     *
     * @return Vector of ElementsInfo for the menu
     */
    std::vector<ElementsInfo> createButtons() const override;
};

/**
 * Menu that shows the top leaderboard entries
 *
 * LeaderboardMenu is responsible for:
 * - Displaying a list of highscore entries from Leaderboard
 * - Providing a back button to return to start menu
 * - Listening to StateMachine and opening when in leaderboard state
 */
class LeaderboardMenu : public Menu
{
  public:
    LeaderboardMenu();

  private:
    /**
     * Create the menu elements for the leaderboard menu
     *
     * @return Vector of ElementsInfo for the menu
     */
    std::vector<ElementsInfo> createButtons() const override;
};

/**
 * Menu for choosing a username before starting the game
 *
 * ChooseNameMenu is responsible for:
 * - Collecting username input from text events
 * - Submitting username and starting the game
 * - Listening to StateMachine and opening when choosing username state
 */
class ChooseNameMenu : public Menu
{
  public:
    ChooseNameMenu();

    /**
     * Handle input events for writing and deleting username characters (+ default)
     *
     * @param event The event to handle
     * @return true if the event was handled
     */
    bool handleEvent(sf::Event const &event) override;

  private:
    /**
     * Create the default menu elements for choosing a username
     *
     * @return Vector of ElementsInfo for the menu
     */
    std::vector<ElementsInfo> createButtons() const override;

    /**
     * Create menu elements with the current username text
     *
     * @param username Username text to display
     * @return Vector of ElementsInfo for the menu
     */
    std::vector<ElementsInfo> createButtons(std::string const &username) const;

    std::string username;
};

/**
 * Pause menu shown when the game is paused
 *
 * PauseMenu is responsible for:
 * - Showing continue, give up, and exit options
 * - Handling pause key events when in game state
 * - Listening to StateMachine and opening when paused state
 */
class PauseMenu : public Menu
{
  public:
    PauseMenu();

    /**
     * Handle input events for pausing and navigating pause menu options (+ default)
     *
     * @param event The event to handle
     * @return true if the event was handled
     */
    bool handleEvent(sf::Event const &event) override;

  private:
    /**
     * Create the menu elements for the pause menu
     *
     * @return Vector of ElementsInfo for the menu
     */
    std::vector<ElementsInfo> createButtons() const override;
};

/**
 * Game over menu shown when the player dies
 *
 * GameOverMenu is responsible for:
 * - Showing restart, main menu, and exit options
 * - Listening to StateMachine and opening when game over state
 */
class GameOverMenu : public Menu
{
  public:
    GameOverMenu();

  private:
    /**
     * Create the menu elements for the game over menu
     *
     * @return Vector of ElementsInfo for the menu
     */
    std::vector<ElementsInfo> createButtons() const override;
};

/**
 * Level up menu shown when the player levels up
 *
 * LevelUpMenu is responsible for:
 * - Displaying level up options provided by ExperienceManager
 * - Creating clickable menu options with callbacks
 * - Listening to StateMachine and opening when level up screen state
 */
class LevelUpMenu : public Menu
{
  public:
    LevelUpMenu();

    /**
     * Replace the menu buttons with new level up options
     *
     * @param levelUpOptions Available level up options
     */
    void createOptions(std::vector<LevelUpInfo> const &levelUpOptions);
    using Menu::setButtons;

  private:
    /**
     * Create menu elements from provided level up options
     *
     * @param levelUpOptions Available level up options
     * @return Vector of ElementsInfo for the menu
     */
    std::vector<ElementsInfo> createButtons(std::vector<LevelUpInfo> const &levelUpOptions) const;

    /**
     * Create default menu elements for this menu (doesn't really do nun)
     *
     * @return Empty vector of ElementsInfo
     */
    std::vector<ElementsInfo> createButtons() const override;
};

#endif