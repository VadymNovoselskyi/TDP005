#include "Highscore.h"

#include <iostream>
#include <stdexcept>

#include "GameState.h"
#include "Window.h"

Highscore *Highscore::instancePtr{nullptr};

// Static methods:
Highscore *Highscore::instance()
{
    if (Highscore::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init Highscore before calling instance on it");
    }
    return Highscore::instancePtr;
}

Highscore *Highscore::init(int scorePerFrame)
{
    Highscore::instancePtr = new Highscore(scorePerFrame);
    return Highscore::instancePtr;
}

void Highscore::deleteInstance()
{
    delete Highscore::instancePtr;
    Highscore::instancePtr = nullptr;
}

// Instance methods
Highscore::Highscore(int scorePerFrame)
    : scorePerFrame{scorePerFrame}, score{0}, timeSurvived{0}, enemiesKilled{0}, highscoreText{}
{
    font.loadFromFile("static/Orbitron-Bold.ttf");

    highscoreText.setFont(font);
    highscoreText.setFillColor(sf::Color::Black);
    highscoreText.setCharacterSize(40);
}

void Highscore::draw(sf::RenderWindow *window)
{
    auto viewCenter = window->getView().getCenter();
    auto viewSize = window->getView().getSize();
    sf::Vector2f pos{viewCenter.x + viewSize.x / 2.0f - 10, viewCenter.y - viewSize.y / 2.0f};

    highscoreText.setPosition(pos);
    highscoreText.setString(std::to_string(score));

    auto bounds = highscoreText.getLocalBounds();
    highscoreText.setOrigin(bounds.left + bounds.width, 0);

    window->draw(highscoreText);

    addSurvivalScore();
}

void Highscore::addKillScore(int extraScore)
{
    score += extraScore;
    enemiesKilled++;
}

void Highscore::addSurvivalScore()
{
    score += scorePerFrame;
}

ScoreInfo Highscore::getScoreInfo() const
{
    return {score, static_cast<int>(score / scorePerFrame), enemiesKilled};
}
