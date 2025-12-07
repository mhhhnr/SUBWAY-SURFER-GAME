#include "scoremanager.h"
#include <fstream>
#include <iostream>
using namespace std;

using namespace std;

ScoreManager::ScoreManager()
    : currentScore(0), highScore(0), playerName("Player"), highScorePlayer("None") {
    loadHighScore();
}

void ScoreManager::loadHighScore() {
    ifstream file(filename);
    if (file.is_open()) {
        file >> highScore;
        getline(file, highScorePlayer);
        getline(file, highScorePlayer);
        file.close();
    }
}

void ScoreManager::saveHighScore() {
    if (currentScore > highScore) {
        highScore = currentScore;
        highScorePlayer = playerName;

        ofstream file(filename);
        if (file.is_open()) {
            file << highScore << endl;
            file << highScorePlayer << endl;
            file.close();
        }
    }
}

void ScoreManager::addScore(int points) {
    currentScore += points;
}

void ScoreManager::reset() {
    currentScore = 0;
}

int ScoreManager::getCurrentScore() const {
    return currentScore;
}

int ScoreManager::getHighScore() const {
    return highScore;
}

string ScoreManager::getHighScorePlayer() const {
    return highScorePlayer;
}

void ScoreManager::setPlayerName(const string& name) {
    playerName = name;
}

void ScoreManager::setCurrentScore(int score) {
    currentScore = score;
}