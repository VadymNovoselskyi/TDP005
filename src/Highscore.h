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
    static Highscore *init();
    static void deleteInstance();

    void addSurvivalScore(int extraScore, int timeMs);
    void addKillScore(int extraScore);

    ScoreInfo getScoreInfo() const;

  private:
    Highscore();
    ~Highscore();
    static Highscore *instancePtr;

    int score;
    int timeSurvived;
    int enemiesKilled;
};

#endif