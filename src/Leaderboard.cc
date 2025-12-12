#include "Leaderboard.h"

#include <fstream>
#include <iostream>
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
    auto existingHighscore = highscores.find(username);
    if (existingHighscore == highscores.end())
    {
        highscores.insert({username, scoreInfo});
    }
    else if (scoreInfo.score > existingHighscore->second.score)
    {
        highscores.insert_or_assign(username, scoreInfo);
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

// TODO: sort by total score
std::map<std::string, ScoreInfo> Leaderboard::getLeaderboard(int maxSize) const
{
    std::map<std::string, ScoreInfo> leaderboard{};

    for (auto it{highscores.begin()};
         it != highscores.end() && static_cast<int>(leaderboard.size()) < maxSize;
         ++it)
    {
        leaderboard.insert({it->first, it->second});
    }
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
        highscores.insert({username, {score, timeSurvived, enemiesKilled}});
    }
}
