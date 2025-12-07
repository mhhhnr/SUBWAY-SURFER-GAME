#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "TrackManager.h"
#include "ScoreManager.h"
#include "RailwayTrack.h"

enum class GameState {
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    HIGH_SCORES
};

class GameEngine {
private:
    sf::Music backgroundMusic;
    sf::RenderWindow window;
    Player player;
    TrackManager trackManager;
    ScoreManager scoreManager;
    sf::Clock clock;
    sf::Font font;
    GameState gameState;
    float survivalTimer;
    bool isDayMode;
    int selectedMenuItem;
    sf::RectangleShape menuItems[4];
    std::string menuLabels[4];
    RailwayTrack* trackLeft;
    RailwayTrack* trackMid;
    RailwayTrack* trackRight;
    sf::RectangleShape sideArea[2];
    const std::string saveFileName = "savegame.txt";

    void processInput();
    void handleMenuInput(sf::Keyboard::Key key);
    void handlePauseInput(sf::Keyboard::Key key);
    void handleGameOverInput(sf::Keyboard::Key key);
    void handlePlayingInput(sf::Keyboard::Key key);
    void update(float deltaTime);
    void drawRoads();
    void renderMenu();
    void renderHighScores();
    void renderPause();
    void renderGameOver();
    void renderPlaying();
    void render();
    void startNewGame();
    void saveGame();
    void loadGame();
    void toggleDayNight();

public:
    GameEngine();
    ~GameEngine();
    void run();
};

#endif#pragma once
