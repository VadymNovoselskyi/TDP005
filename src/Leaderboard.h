#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "Highscore.h"

class Leaderboard
{
  public:
    static Leaderboard *instance();
    static Leaderboard *init(std::string const &leaderboardPath);
    static void deleteInstance();

    void saveHighscore(std::string const &username, ScoreInfo const &scoreInfo);
    void saveLeaderboard(std::string const &leaderboard) const;
    std::map<std::string, ScoreInfo> getHighscores() const;

  private:
    Leaderboard(std::string const &leaderboardPath);

    static Leaderboard *instancePtr;

    void loadLeaderboard(std::string const &leaderboard);

    std::map<std::string, ScoreInfo> highscores;
};

#endif