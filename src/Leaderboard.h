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
    void saveLeaderboard(std::string const &leaderboardPath) const;
    std::vector<std::pair<std::string, ScoreInfo>> getLeaderboard(int maxSize);

  private:
    Leaderboard(std::string const &leaderboardPath);

    static Leaderboard *instancePtr;

    void loadLeaderboard(std::string const &leaderboardPath);

    std::vector<std::pair<std::string, ScoreInfo>> highscores;
};

#endif