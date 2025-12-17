#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "Highscore.h"

/**
 * Stores and manages highscore entries for the game
 *
 * Leaderboard is responsible for:
 * - Loading highscores from file
 * - Updating a users highscore if a better score is achieved
 * - Saving highscores to file
 * - Returning a sorted list of highscores for display
 */
class Leaderboard
{
  public:
    /**
     * Get the Leaderboard singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton Leaderboard instance
     * @throws std::logic_error if the Leaderboard has not been initialized
     */
    static Leaderboard *instance();

    /**
     * Create and initialize the Leaderboard singleton
     *
     * @param leaderboardPath Path to the leaderboard file
     * @return Pointer to the created singleton Leaderboard instance
     */
    static Leaderboard *init(std::string const &leaderboardPath);

    /**
     * Destroy the Leaderboard singleton instance
     */
    static void deleteInstance();

    /**
     * Save a highscore entry for a username
     * If the username already exists in the Leaderboard only a better score replaces the stored one
     *
     * @param username The username for the highscore
     * @param scoreInfo The score, time survived and enemies killed
     */
    void saveHighscore(std::string const &username, ScoreInfo const &scoreInfo);

    /**
     * Save the current leaderboard to file
     *
     * @param leaderboardPath Path to the leaderboard file
     */
    void saveLeaderboard(std::string const &leaderboardPath) const;

    /**
     * Get a sorted leaderboard list up to a maximum size
     *
     * @param maxSize Maximum number of entries to return
     * @return Vector of username and ScoreInfo pairs sorted by score
     */
    std::vector<std::pair<std::string, ScoreInfo>> getLeaderboard(int maxSize);

  private:
    /**
     * Create a Leaderboard and load highscores from file
     *
     * @param leaderboardPath Path to the leaderboard file
     */
    Leaderboard(std::string const &leaderboardPath);

    static Leaderboard *instancePtr;

    /**
     * Load highscores from a leaderboard file
     *
     * @param leaderboardPath Path to the leaderboard file
     */
    void loadLeaderboard(std::string const &leaderboardPath);

    std::vector<std::pair<std::string, ScoreInfo>> highscores;
};

#endif