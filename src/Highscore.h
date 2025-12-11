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
    static Highscore *init(int framesPerScore);
    static void deleteInstance();

    void resetState();

    void draw(sf::RenderWindow *window);
    void addKillScore(int extraScore);

    ScoreInfo getScoreInfo() const;

  private:
    Highscore(int scorePerFrame);
    static Highscore *instancePtr;

    void tickSurvivalScore();

    int framesPerScore;
    int scoreCountdown;

    int score;
    int timeSurvived;
    int enemiesKilled;

    sf::Text highscoreText;
    sf::Font font;
};

#endif