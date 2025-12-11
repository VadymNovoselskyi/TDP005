#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <SFML/Graphics.hpp>

struct ScoreInfo
{
    int score;
    int timeSurvived;
    int enemiesKilled;
};

class Highscore
{
  public:
    static Highscore *instance();
    static Highscore *init(int scorePerFrame);
    static void deleteInstance();

    void draw(sf::RenderWindow *window);
    void addKillScore(int extraScore);

    ScoreInfo getScoreInfo() const;

  private:
    Highscore(int scorePerFrame);
    static Highscore *instancePtr;

    void addSurvivalScore();

    int scorePerFrame;
    int score;
    int timeSurvived;
    int enemiesKilled;

    sf::Text highscoreText;
    sf::Font font;
};

#endif