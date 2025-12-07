#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <fstream>

enum class PlayerState {
    RUNNING,
    JUMPING,
    SLIDING
};

class Player {
private:
    // Lane and movement
    int currentLane;
    PlayerState state;
    float yPosition;
    float jumpVelocity;
    float slideTimer;
    bool isMoving;
    sf::RectangleShape playerShape;

    // Power-up states
    bool hasShield;
    float shieldTimer;
    bool hasJetpack;
    float jetpackTimer;
    bool hasMagnet;
    float magnetTimer;
    bool hasDoubleCoin;
    float doubleCoinTimer;

    // Constants
    static const int LANE_WIDTH = 150;
    static const int LEFT_MARGIN = 250;
    static constexpr float JUMP_STRENGTH = -600.0f;
    static constexpr float GRAVITY = 1800.0f;
    static constexpr float SLIDE_DURATION = 0.5f;

    // Visual parts - character model
    sf::CircleShape head;
    sf::RectangleShape capTop;
    sf::RectangleShape capBrim;
    sf::RectangleShape capBill;
    sf::RectangleShape hair;
    sf::RectangleShape torso;
    sf::RectangleShape leftArm;
    sf::RectangleShape rightArm;
    sf::RectangleShape leftLeg;
    sf::RectangleShape rightLeg;
    sf::RectangleShape leftShoe;
    sf::RectangleShape rightShoe;
    sf::Color outfitColor;

    // Helper methods
    void setupVisuals();
    void updateModel();

public:
    // Constructor
    Player();

    // Movement controls
    void moveLeft();
    void moveRight();
    void jump();
    void slide();

    // Power-up activation
    void activateShield(float duration);
    void activateJetpack(float duration);
    void activateMagnet(float duration);
    void activateDoubleCoin(float duration);

    // Game loop methods
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    // Getters
    int getLane() const;
    PlayerState getState() const;
    float getYPosition() const;
    sf::FloatRect getBounds() const;
    bool getHasShield() const;
    bool getHasMagnet() const;
    bool getHasDoubleCoin() const;
    bool getHasJetpack() const;

    // Game state management
    void reset();
    void saveState(std::ofstream& file);
    void loadState(std::ifstream& file);
};

#endif#pragma once
