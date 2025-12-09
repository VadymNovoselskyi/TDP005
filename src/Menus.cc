#include "Menus.h"

#include <iostream>
#include <vector>

#include "Menu.h"
#include "StateMachine.h"

// Start menu
StartMenu::StartMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::IN_START_MENU)
{
    StateMachine::instance()->addListener("StartMenu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::IN_START_MENU); });
}

std::vector<ElementsInfo> StartMenu::createButtons() const
{
    std::vector<ElementsInfo> elements{};

    ElementsInfo title{"GAME NAME", 0.5, 0.1, std::nullopt};
    elements.push_back(title);

    ElementsInfo startButton{
        "START", 0.5, 0.4, []() { StateMachine::instance()->chooseUsername(); }};
    elements.push_back(startButton);

    ElementsInfo rankingsButton{"RANKINGS", 0.5, 0.6, []() {}};
    // "RANKINGS", 0.5, 0.4, []() { StateMachine::instance()->startGame(); }};
    elements.push_back(rankingsButton);

    ElementsInfo exitButton{"EXIT", 0.5, 0.8, []() { StateMachine::instance()->exitGame(); }};
    elements.push_back(exitButton);

    return elements;
}

// Choose name menu
ChooseNameMenu::ChooseNameMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::CHOOSING_USERNAME),
      username{}
{
    StateMachine::instance()->addListener(
        "ChooseNameMenu",
        [this](GameState gameState) { setIsOpen(gameState == GameState::CHOOSING_USERNAME); });
}

std::vector<ElementsInfo> ChooseNameMenu::createButtons() const
{
    return createButtons("*YOUR USERNAME*");
}

// Done this because cant init username in the constructor because of reordering
std::vector<ElementsInfo> ChooseNameMenu::createButtons(std::string const &username) const
{
    std::vector<ElementsInfo> elements{};

    ElementsInfo title{"CHOOSE YOUR USERNAME", 0.5, 0.1, std::nullopt};
    elements.push_back(title);

    ElementsInfo nameField{username, 0.5, 0.4, std::nullopt};
    elements.push_back(nameField);

    ElementsInfo submitButton{"SUBMIT", 0.5, 0.6, []() { StateMachine::instance()->startGame(); }};
    elements.push_back(submitButton);

    return elements;
}
bool ChooseNameMenu::handleEvent(sf::Event event)
{
    bool handled = Menu::handleEvent(event);
    if (handled)
    {
        return true;
    }

    if (StateMachine::instance()->state() == GameState::CHOOSING_USERNAME &&
        event.type == sf::Event::TextEntered)
    // Only add the ASCII chars, seems good enough for now
    // The unicode values are taken from https://en.wikipedia.org/wiki/List_of_Unicode_characters
    {
        if (event.text.unicode <= 126 && event.text.unicode >= 32 && username.length() < 20)
        {
            username += event.text.unicode;
            Menu::setButtons(createButtons(username));
        }

        // The backspace button
        else if (event.text.unicode == 8)
        {
            if (username.length() > 0)
            {
                username.erase(username.length() - 1);
                Menu::setButtons(createButtons(username));
            }
        }
        return true;
    }
    return false;
}

// Pause menu
PauseMenu::PauseMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::GAME_PAUSED)
{
    StateMachine::instance()->addListener("PauseMenu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::GAME_PAUSED); });
}

std::vector<ElementsInfo> PauseMenu::createButtons() const
{
    std::vector<ElementsInfo> elements{};

    ElementsInfo title{"GAME PAUSED", 0.5, 0.1, std::nullopt};
    elements.push_back(title);

    ElementsInfo continueButton{
        "CONTINUE", 0.5, 0.4, []() { StateMachine::instance()->continueGame(); }};
    elements.push_back(continueButton);

    ElementsInfo giveUpButton{
        "GIVE UP", 0.5, 0.6, []() { StateMachine::instance()->finishGame(); }};
    elements.push_back(giveUpButton);

    ElementsInfo exitButton{"EXIT", 0.5, 0.8, []() { StateMachine::instance()->exitGame(); }};
    elements.push_back(exitButton);

    return elements;
}

bool PauseMenu::handleEvent(sf::Event event)
{
    bool handled = Menu::handleEvent(event);
    if (handled)
    {
        return true;
    }

    if (StateMachine::instance()->state() == GameState::IN_GAME &&
        event.type == sf::Event::KeyPressed &&
        (event.key.scancode == sf::Keyboard::Scan::Space ||
         event.key.scancode == sf::Keyboard::Scan::Escape))
    {
        StateMachine::instance()->pauseGame();
        return true;
    }
    return false;
}

// Game Over menu
GameOverMenu::GameOverMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::GAME_OVER)
{
    StateMachine::instance()->addListener("GameOverMenu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::GAME_OVER); });
}

std::vector<ElementsInfo> GameOverMenu::createButtons() const
{
    std::vector<ElementsInfo> elements{};

    ElementsInfo title{"GAME OVER", 0.5, 0.1, std::nullopt};
    elements.push_back(title);

    ElementsInfo restartButton{
        "RESTART", 0.5, 0.4, []() { StateMachine::instance()->startGame(); }};
    elements.push_back(restartButton);

    ElementsInfo mainMenuButton{
        "MAIN MENU", 0.5, 0.6, []() { StateMachine::instance()->openStartMenu(); }};
    elements.push_back(mainMenuButton);

    ElementsInfo exitButton{"EXIT", 0.5, 0.8, []() { StateMachine::instance()->exitGame(); }};
    elements.push_back(exitButton);

    return elements;
}

// Level Up menu
LevelUpMenu::LevelUpMenu()
    : Menu(createButtons(), StateMachine::instance()->state() == GameState::LEVEL_UP_SCREEN)
{
    StateMachine::instance()->addListener("LevelUpMenu",
                                          [this](GameState gameState)
                                          { setIsOpen(gameState == GameState::LEVEL_UP_SCREEN); });
}

void LevelUpMenu::createOptions(std::vector<LevelUpInfo> const &levelUpOptions)
{
    Menu::setButtons(createButtons(levelUpOptions));
}

std::vector<ElementsInfo>
LevelUpMenu::createButtons(std::vector<LevelUpInfo> const &levelUpOptions) const
{
    float PADDING_TOP{0.3};
    float PADDING_BOTTOM{0.2};
    int optionsSize{static_cast<int>(levelUpOptions.size())};
    std::vector<ElementsInfo> elements{static_cast<unsigned long>(optionsSize + 1)};

    ElementsInfo title{"Choose your level up", 0.5, 0.1, std::nullopt};
    elements.push_back(title);
    for (int i{0}; i < optionsSize; ++i)
    {
        auto levelUpOption = levelUpOptions.at(i);
        ElementsInfo levelUpButton{
            levelUpOption.description,
            0.5,
            (((1 - PADDING_TOP - PADDING_BOTTOM) / optionsSize * i) + PADDING_TOP),
            levelUpOption.onClick};
        elements.push_back(levelUpButton);
    }
    return elements;
}

std::vector<ElementsInfo> LevelUpMenu::createButtons() const
{
    return std::vector<ElementsInfo>{};
}
