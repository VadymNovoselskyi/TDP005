#include "Leaderboard.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

Leaderboard *Leaderboard::instancePtr{nullptr};

// Static methods:
Leaderboard *Leaderboard::instance()
{
    if (Leaderboard::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init Leaderboard before calling instance on it");
    }
    return Leaderboard::instancePtr;
}

Leaderboard *Leaderboard::init(std::string const &leaderboardPath)
{
    Leaderboard::instancePtr = new Leaderboard(leaderboardPath);
    return Leaderboard::instancePtr;
}

void Leaderboard::deleteInstance()
{
    delete Leaderboard::instancePtr;
    Leaderboard::instancePtr = nullptr;
}

// Instance methods
Leaderboard::Leaderboard(std::string const &leaderboardPath) : highscores{}
{
    loadLeaderboard(leaderboardPath);
}

void Leaderboard::saveHighscore(std::string const &username, ScoreInfo const &scoreInfo)
{
    auto existingHighscore =
        std::find_if(highscores.begin(),
                     highscores.end(),
                     [&username](auto &highscore) { return highscore.first == username; });
    if (existingHighscore == highscores.end())
    {
        highscores.emplace_back(username, scoreInfo);
    }
    else if (scoreInfo.score > existingHighscore->second.score)
    {
        existingHighscore->second = scoreInfo;
    }
}

void Leaderboard::saveLeaderboard(std::string const &leaderboardPath) const
{
    // File read syntax was taken from https: // www.w3schools.com/cpp/cpp_files.asp
    std::ofstream file(leaderboardPath);

    for (auto &[username, highscore] : highscores)
    {
        file << username << " " << highscore.score << " " << highscore.timeSurvived << " "
             << highscore.enemiesKilled << "\n";
    }
    file.close();
}

std::vector<std::pair<std::string, ScoreInfo>> Leaderboard::getLeaderboard(int maxSize)
{
    std::vector<std::pair<std::string, ScoreInfo>> leaderboard{};
    std::sort(highscores.begin(),
              highscores.end(),
              [](auto &a, auto &b) { return a.second.score > b.second.score; });
    std::copy_n(highscores.begin(), maxSize, std::back_inserter(leaderboard));

    return leaderboard;
}

void Leaderboard::loadLeaderboard(std::string const &leaderboardPath)
{
    std::ifstream file(leaderboardPath);

    if (!file.is_open())
    {
        throw std::logic_error("Couldn't open the leaderboard file");
    }

    // The loop is kinda taken from TileManager
    for (std::string line{}; std::getline(file, line, '\n');)
    {
        std::istringstream lineStream{line};
        std::string username{};
        int score{};
        int timeSurvived{};
        int enemiesKilled{};

        lineStream >> username >> score >> timeSurvived >> enemiesKilled;
        highscores.push_back({username, {score, timeSurvived, enemiesKilled}});
    }
}
