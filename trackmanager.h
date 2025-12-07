#ifndef TRACKMANAGER_H
#define TRACKMANAGER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include "GameList.h"
#include "Obstacle.h"
#include "Coin.h"
#include "PowerUp.h"
#include "Player.h"
#include "ScoreManager.h"

class TrackManager {
private:
    // Game object collections
    GameList<Obstacle*> obstacles;
    GameList<Coin*> coins;
    GameList<PowerUp*> powerups;

    // Spawn timers
    float spawnTimer;
    float coinSpawnTimer;
    float powerupSpawnTimer;

    // Speed management
    float baseSpeed;
    float currentSpeed;

public:
    // Constructor and destructor
    TrackManager();
    ~TrackManager();

    // Memory management
    void clearAll();

    // Game loop methods
    void update(float deltaTime, Player& player, ScoreManager& scoreManager);
    void render(sf::RenderWindow& window);

    // Spawning methods
    void spawnObstacle();
    void spawnCoin();
    void spawnPowerUp();

    // Collision detection
    bool checkCollisions(Player& player);

    // Game state management
    void reset();
    void saveState(std::ofstream& file);
    void loadState(std::ifstream& file);
};

#endif#pragma once
