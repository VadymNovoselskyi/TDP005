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
    
    void setUsername(std::string const& username);
    void saveHighscore() const;
    void resetState();
    
    void draw(sf::RenderWindow *window);
    void addKillScore(int extraScore);

  private:
    Highscore(int framesPerScore);
    static Highscore *instancePtr;

    void tickSurvivalScore();

    int framesPerScore;
    int scoreCountdown;

    int score;
    int timeSurvived;
    int enemiesKilled;

    std::string username;

    sf::Text highscoreText;
    sf::Font font;
};

#endif