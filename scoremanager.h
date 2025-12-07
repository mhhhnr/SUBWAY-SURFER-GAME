#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <string>

class ScoreManager {
private:
    // Score tracking
    int currentScore;
    int highScore;

    // Player information
    std::string playerName;
    std::string highScorePlayer;

    // File management
    const std::string filename = "highscore.txt";

public:
    // Constructor
    ScoreManager();

    // File operations
    void loadHighScore();
    void saveHighScore();

    // Score management
    void addScore(int points);
    void reset();

    // Getters
    int getCurrentScore() const;
    int getHighScore() const;
    std::string getHighScorePlayer() const;

    // Setters
    void setPlayerName(const std::string& name);
    void setCurrentScore(int score);
};

#endif#pragma once
