#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <SFML/Graphics.hpp>

struct ScoreInfo
{
    int score;
    int timeSurvived;
    int enemiesKilled;
};

/**
 * Manages player score tracking and display
 *
 * Highscore is responsible for:
 * - Tracking score, time survived, and enemies killed
 * - Incrementing survival score over time and for killing enemies
 * - Drawing the current score on screen
 * - Saving highscore data with Leaderboard
 */
class Highscore
{
  public:
    /**
     * Get the Highscore singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton Highscore instance
     * @throws std::logic_error if the Highscore has not been initialized
     */
    static Highscore *instance();
    
    /**
     * Create and initialize the Highscore singleton
     *
     * @param framesPerScore Number of frames between survival score increments
     * @return Pointer to the created singleton Highscore instance
     */
    static Highscore *init(int framesPerScore);
    
    /**
     * Destroy the Highscore singleton instance
     */
    static void deleteInstance();
    
    /**
     * Set the username associated with the highscore
     *
     * @param username The username to set
     */
    void setUsername(std::string const& username);
    
    /**
     * Save the current highscore to the Leaderboard
     */
    void saveHighscore() const;
    
    /**
     * Reset score, time survived, and enemies killed to initial state
     */
    void resetState();
    
    /**
     * Draw the current score on the RenderWindow
     * Also ticks survival score if in game state
     *
     * @param window The RenderWindow to draw into
     */
    void draw(sf::RenderWindow *window);
    
    /**
     * Add score for killing an enemy
     *
     * @param extraScore Additional score points to add
     */
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